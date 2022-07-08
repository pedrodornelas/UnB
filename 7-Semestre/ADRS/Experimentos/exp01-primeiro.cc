/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 * Changed by : Claudia Jacy Barenco Abbas 
 */

#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/applications-module.h"
#include "ns3/flow-monitor-helper.h"              //Para uso do FlowMonitor
#include "ns3/flow-monitor.h"
#include "ns3/ipv4-flow-classifier.h"             //Para classificador do fluxo

using namespace ns3;

NS_LOG_COMPONENT_DEFINE ("Primeiro");

int
main (int argc, char *argv[])
{

   uint32_t nPackets=1000000;
   std::string DataRate="5Mbps";
   std::string Delay="2ms";
   uint32_t time = 10;

   CommandLine cmd;  
   // Alteracao do Numero de pacotes a serem transmitidos
   cmd.AddValue("nPackets","Numero de pacotes para enviar no echo",nPackets);
   // Alteracao da Taxa de Dados na Camada de Enlace  
   cmd.AddValue("DataRate","Taxa de dados no enlace Ponto a Ponto",DataRate);
   cmd.AddValue("Delay","Atraso de Propagacao no enlace Ponto a Ponto",Delay);
   cmd.AddValue("Time","Tempo de Simulacao",time);
   cmd.Parse (argc, argv);
  
  Time::SetResolution (Time::NS);
  LogComponentEnable ("UdpEchoClientApplication", LOG_LEVEL_INFO);
  LogComponentEnable ("UdpEchoServerApplication", LOG_LEVEL_INFO);

  NodeContainer nodes;
  nodes.Create (2);

  PointToPointHelper pointToPoint;
  pointToPoint.SetDeviceAttribute ("DataRate", StringValue (DataRate));
  pointToPoint.SetChannelAttribute ("Delay", StringValue (Delay));

  NetDeviceContainer devices;
  devices = pointToPoint.Install (nodes);

  InternetStackHelper stack;
  stack.Install (nodes);

  Ipv4AddressHelper address;
  address.SetBase ("10.1.1.0", "255.255.255.0");

  Ipv4InterfaceContainer interfaces = address.Assign (devices);

  UdpEchoServerHelper echoServer (9);

  ApplicationContainer serverApps = echoServer.Install (nodes.Get (1));
  serverApps.Start (Seconds (1.0));
  serverApps.Stop (Seconds (time));

  UdpEchoClientHelper echoClient (interfaces.GetAddress (1), 9);
  echoClient.SetAttribute ("MaxPackets", UintegerValue (nPackets));
  echoClient.SetAttribute ("Interval", TimeValue (Seconds (0.06)));
  echoClient.SetAttribute ("PacketSize", UintegerValue(1024));

  ApplicationContainer clientApps = echoClient.Install (nodes.Get (0));
  clientApps.Start (Seconds (2.0));
  clientApps.Stop (Seconds (time));

  AsciiTraceHelper ascii;
  pointToPoint.EnableAsciiAll(ascii.CreateFileStream("Primeiro.tr"));
  
  // Configura o rastreamento (pcap) para WireShark
  pointToPoint.EnablePcapAll ("Primeiro");

  // Instala FlowMonitor em todos os nos 
  FlowMonitorHelper flowmon;
  Ptr<FlowMonitor> monitor = flowmon.InstallAll ();

  Simulator::Stop (Seconds (time));
  Simulator::Run ();

  // Mostra estatisticas por fluxo
  monitor->CheckForLostPackets ();
  Ptr<Ipv4FlowClassifier> classifier = DynamicCast<Ipv4FlowClassifier> (flowmon.GetClassifier ());
  std::map<FlowId, FlowMonitor::FlowStats> stats = monitor->GetFlowStats ();
  for (std::map<FlowId, FlowMonitor::FlowStats>::const_iterator i = stats.begin (); i != stats.end (); ++i)
    {
          Ipv4FlowClassifier::FiveTuple t = classifier->FindFlow (i->first);
          std::cout << "Flow " << i->first - 1 << " (" << t.sourceAddress << " -> " << t.destinationAddress << ")\n";
          std::cout << "  Tx Packets: " << i->second.txPackets << "\n";
          std::cout << "  Tx Bytes:   " << i->second.txBytes << "\n";
          std::cout << "  TxOffered:  " << ((i->second.txBytes * 8.0)/((i->second.timeLastTxPacket.GetSeconds())))  << " bps\n";
          std::cout << "  Rx Packets: " << i->second.rxPackets << "\n";
          std::cout << "  Rx Bytes:   " << i->second.rxBytes << "\n";
          std::cout << "  Throughput: " << ((i->second.rxBytes * 8.0)/ ((i->second.timeLastRxPacket.GetSeconds())))  << " bps\n";
          std::cout << "  Delay medio: " << i->second.delaySum.GetSeconds()/i->second.rxPackets << "\n";
		  std::cout << "  Jitter medio: " << i->second.jitterSum.GetSeconds()/(i->second.rxPackets -1) << "\n";
       }

  Simulator::Destroy ();
  return 0;
}
