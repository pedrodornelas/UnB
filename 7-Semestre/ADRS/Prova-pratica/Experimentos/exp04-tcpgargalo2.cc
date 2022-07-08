/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2012 NICT
 *
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
 *
 * Author: Hajime Tazaki <tazaki@nict.go.jp>
 *
 * Modified by: Claudia Jacy Barenco Abbas
 *
 */

#include "ns3/log.h"
#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/applications-module.h"
#include "ns3/flow-monitor-module.h"
#include "ns3/rng-seed-manager.h"

using namespace ns3;

NS_LOG_COMPONENT_DEFINE ("TCPGargalo");

std::string sock_factory; 
std::ofstream meuarquivo1("RajJain",std::ios_base::app); // Arquivode plot de justiça
std::ofstream meuarquivo2("Goodput",std::ios_base::app); // Arquivo de plot do goodput
std::ofstream meuarquivo3("RajJainTotal",std::ios_base::app); // Arquivode plot de justiça

int
main (int argc, char *argv[])
{
  double startTime = 4.0; // Tempo de início de simulação
  double stopTime = 20.0;// Tempo de parada de simulação
  uint32_t m_nNodes = 2;  // Número de nós
  
  CommandLine cmd;
  cmd.AddValue ("nNodes", "the number of source and sink nodes", m_nNodes);
  cmd.AddValue ("stopTime", "duration", stopTime);
  cmd.Parse (argc, argv);

  // Cria os nós
  NodeContainer lefts, routers, rights, nodes; 
  lefts.Create (m_nNodes);
  routers.Create (2);
  rights.Create (m_nNodes);
  nodes = NodeContainer (lefts, routers, rights); 

  // Instala pilha TCP/IP em todos os nós
  InternetStackHelper internetStack;
  internetStack.InstallAll();

  GlobalValue::Bind ("ChecksumEnabled", BooleanValue (true));
  
  // Links p2p
  PointToPointHelper pointToPoint, pointToPoint2;
  pointToPoint.SetDeviceAttribute ("DataRate", StringValue ("5Mbps"));
  pointToPoint.SetChannelAttribute ("Delay", StringValue ("100us"));
  pointToPoint2.SetDeviceAttribute ("DataRate", StringValue ("5Mbps"));
  pointToPoint2.SetChannelAttribute ("Delay", StringValue ("100ms"));

  // Endereçamento IP
  Ipv4AddressHelper address;
  Ipv4InterfaceContainer interfaces;  

  // Instala os links no lado esquerdo da rede
  NetDeviceContainer dev0, dev1, dev2;
  for (uint32_t i = 0; i < m_nNodes; i++)
  {
    std::ostringstream oss;
    oss << "10.0." << i << ".0";
    address.SetBase (oss.str ().c_str (), "255.255.255.0");
    
    if (i%2==0) dev0 = pointToPoint2.Install (NodeContainer (lefts.Get (i), routers.Get (0)));
    else dev0 = pointToPoint.Install (NodeContainer (lefts.Get (i), routers.Get (0)));
    address.Assign (dev0);
  }

  // Instala o link p2p entre os dois roteadores
  pointToPoint.SetDeviceAttribute ("DataRate", StringValue ("20Mbps"));
  pointToPoint.SetChannelAttribute ("Delay", StringValue ("200ms"));
  dev1 = pointToPoint.Install (NodeContainer (routers.Get (0), routers.Get (1)));

  address.SetBase("10.1.0.0", "255.255.255.0");
  address.Assign (dev1);

  pointToPoint.SetDeviceAttribute ("DataRate", StringValue ("5Mbps"));
  pointToPoint.SetChannelAttribute ("Delay", StringValue ("100us"));

  // Instala os links do lado direito da rede  
  for (uint32_t i = 0; i < m_nNodes; i++)
    {
      std::ostringstream oss;
      oss << "10.2." << i << ".0";
      address.SetBase (oss.str ().c_str (), "255.255.255.0");
      dev2 = pointToPoint.Install (NodeContainer (routers.Get (1), rights.Get (i)));
      address.Assign (dev2);
    }


  Ptr<RateErrorModel> em1 =
      CreateObjectWithAttributes<RateErrorModel> (
        "ErrorRate", DoubleValue (0.0001),
        "ErrorUnit", EnumValue (RateErrorModel::ERROR_UNIT_PACKET)
  );

  dev1.Get (1)->SetAttribute ("ReceiveErrorModel", PointerValue (em1));
  dev1.Get (0)->SetAttribute ("ReceiveErrorModel", PointerValue (em1));

  Ipv4GlobalRoutingHelper::PopulateRoutingTables ();
  
  Config::SetDefault ("ns3::TcpSocket::SegmentSize", UintegerValue (512)); // MSS
  Config::SetDefault ("ns3::TcpSocket::DelAckCount", UintegerValue (1));  // ACKs esperados para transmitir próximo pacote

  // Versão TCP
  Config::SetDefault ("ns3::TcpL4Protocol::SocketType", StringValue ("ns3::TcpVegas"));


  sock_factory = "ns3::TcpSocketFactory";
  
  ApplicationContainer apps;

  // Aplicação On-Off sobre TCP
  OnOffHelper onoff = OnOffHelper (sock_factory,
                                   InetSocketAddress (Ipv4Address ("10.2.0.2"), 2000));    
  onoff.SetAttribute ("OnTime", StringValue ("ns3::UniformRandomVariable"));     
  onoff.SetAttribute ("OffTime", StringValue ("ns3::UniformRandomVariable"));  
  onoff.SetAttribute ("PacketSize", StringValue ("1024"));
  onoff.SetAttribute ("DataRate", StringValue ("5Mbps"));
  
  // Flow 1 - n
  for (uint32_t i = 0; i < m_nNodes; i++)
    {
      std::ostringstream oss;
      oss << "10.2." << i << ".2";
    
      if (i%2==0){
        onoff.SetAttribute ("Remote", AddressValue (InetSocketAddress (Ipv4Address (oss.str ().c_str ()), 2000)));
        apps = onoff.Install (lefts.Get (i));}
      else {
        // Aplicação CBR sobre UDP
        UdpClientHelper udpClient (Ipv4Address (oss.str ().c_str ()), 4000);
        udpClient.SetAttribute ("MaxPackets", UintegerValue (4294967295));
        udpClient.SetAttribute ("Interval", TimeValue (Seconds(0.0016)));
        udpClient.SetAttribute ("PacketSize", UintegerValue (1024));
        apps = udpClient.Install (lefts.Get (i));}

      apps.Start(Seconds(startTime));
      apps.Stop(Seconds(stopTime));
}

  // Aplicação TCP Sink
  PacketSinkHelper sink = PacketSinkHelper (sock_factory,
                                            InetSocketAddress (Ipv4Address::GetAny (), 2000)); 
  apps = sink.Install (rights);
  apps.Start (Seconds (0));
  apps.Stop (Seconds (stopTime));

  // Aplicação UDP Server
  ApplicationContainer apps2;
  UdpServerHelper udpServer (4000);
  apps2 = udpServer.Install (rights);
  apps2.Start (Seconds (0.0));
  apps2.Stop (Seconds (stopTime));

  // Habilita o rastreamento ascii
  AsciiTraceHelper ascii;
  pointToPoint.EnableAsciiAll(ascii.CreateFileStream("TCPGargaloVegas.tr"));

  // Habilita o rastreamento pcap em todos os nós
  //pointToPoint.EnablePcapAll ("TCPGargaloVegas");

  // Instala FlowMonitor em todos os nós 
  FlowMonitorHelper flowmon;
  Ptr<FlowMonitor> monitor = flowmon.InstallAll ();
  
  Simulator::Stop (Seconds (stopTime));

  Simulator::Run ();

   Ptr<Ipv4FlowClassifier> classifier = DynamicCast<Ipv4FlowClassifier> (flowmon.GetClassifier ());
  std::map<FlowId, FlowMonitor::FlowStats> stats = monitor->GetFlowStats ();

  Ptr<PacketSink> pktsink;
  double somaquadrados=0.0;
  double soma=0.0;
  double calcula=0.0;

  uint32_t sinkId = 0;

  for (std::map<FlowId, FlowMonitor::FlowStats>::const_iterator i = stats.begin (); i != stats.end (); ++i)
  {
    Ipv4FlowClassifier::FiveTuple t = classifier->FindFlow (i->first);
    std::cout << "Flow " << i->first << " (" << t.sourceAddress << " -> " << t.destinationAddress << ")\n";
    std::cout << "  Protocolo: " << t.protocol+0 << "\n";
    std::cout << "  Tx Pacotes: " << i->second.txPackets << "\n";
    std::cout << "  Tx Aplicação:  " << ((i->second.txBytes * 8.0)/(i->second.timeLastRxPacket.GetSeconds()-i->second.timeFirstRxPacket.GetSeconds()))  << " bps\n";
    std::cout << "  Rx Pacotes: " << i->second.rxPackets << "\n";
    std::cout << "  Rx Taxa de bits média: " << ((i->second.rxBytes * 8.0)/ (i->second.timeLastRxPacket.GetSeconds()-i->second.timeFirstRxPacket.GetSeconds()))  << " bps\n";

    if (i->first-1 < m_nNodes){

        if (t.protocol+0==6){
          pktsink = apps.Get (sinkId)->GetObject<PacketSink> ();
          calcula = pktsink->GetTotalRx () * 8 / (stopTime - startTime);
          std::cout << "  Goodput:  " << pktsink->GetTotalRx () << " bytes (" << calcula << " bps) \n";
          sinkId += 2;}
        else{
          calcula = (i->second.rxBytes-i->second.rxPackets-28.0) * 8.0 / (stopTime - startTime);      
          std::cout << "  Goodput:  " << i->second.rxBytes-i->second.rxPackets*28.0 << " bytes (" << calcula << " bps) \n";}               
   
        somaquadrados=somaquadrados+calcula*calcula;
        soma=soma+calcula;
        meuarquivo2 << calcula/1000 << ",";

      }

    std::cout << "  Atraso médio: " << i->second.delaySum.GetSeconds()/i->second.rxPackets << "\n";
    std::cout << "  Jitter médio: " << i->second.jitterSum.GetSeconds()/(i->second.rxPackets -1) << "\n";
    std::cout << "  Número de pacotes perdidos: " << i->second.lostPackets << "\n";
     }
  meuarquivo2 << std::endl;
  //calcula Raj Jain
  std::cout << "\nJustica Raj Jain e: " << (soma*soma)/(m_nNodes*somaquadrados) << std::endl;
  meuarquivo1 << m_nNodes << "," << (soma*soma)/(m_nNodes*somaquadrados) << std::endl;
  meuarquivo3 << (soma*soma)/(m_nNodes*somaquadrados);
  Simulator::Destroy ();
  return 0;
}
