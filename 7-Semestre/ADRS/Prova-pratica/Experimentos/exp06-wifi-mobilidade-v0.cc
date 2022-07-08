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
 */

#include <string>
#include "ns3/core-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/network-module.h"
#include "ns3/applications-module.h"
#include "ns3/wifi-module.h"
#include "ns3/mobility-module.h"
#include "ns3/csma-module.h"
#include "ns3/internet-module.h"
#include "ns3/flow-monitor-helper.h"              //Para uso do FlowMonitor
#include "ns3/flow-monitor.h"
#include "ns3/ipv4-flow-classifier.h"             //Para classificador do fluxo
#include "ns3/wifi-remote-station-manager.h"
#include "ns3/netanim-module.h"                   // NetAnim

// Modificado por: Claudia Jacy Barenco Abbas 

// Default Network Topology
//
// Number of wifi 
//   Wifi 
//                 AP
//  *    *    *    *
//  |    |    |    |    
// n0   n1   n2   n3 
//

using namespace ns3;

NS_LOG_COMPONENT_DEFINE ("WiFi");

void
CourseChange (std::string context, Ptr<const MobilityModel> model)
{
   Vector position = model->GetPosition ();
   NS_LOG_UNCOND (context << " x = " << position.x << ", y = " << position.y);
}

int 
main (int argc, char *argv[])
{
  uint32_t nWifi = 3;
  uint32_t packet_s=1024;
  double distance=3;
  std::string speed1="10.0";
  std::string speed2="20.0";
  AnimationInterface * pAnim = 0;

  CommandLine cmd;
  cmd.AddValue ("distance", "distance (m)", distance);
  cmd.AddValue ("speed1","mínima velocidade (m/s)",speed1);
  cmd.AddValue ("speed2","máxima velocidade (m/s)",speed2);
  cmd.AddValue ("nWifi","Número de estações",nWifi);
  cmd.AddValue ("speed2","máxima velocidade (m/s)",speed2);
  cmd.Parse (argc,argv);

  // Check for valid number of csma or wifi nodes
  // otherwise IP addresses 

  if (nWifi > 250)
    {
      std::cout << "Too many wifi, no more than 250 each." << std::endl;
      return 1;
    }

  // Cria estações wireless
  NodeContainer wifiStaNodes;
  wifiStaNodes.Create (nWifi);

  // Cria um AP
  NodeContainer wifiApNode;
  wifiApNode.Create(1);

  YansWifiChannelHelper channel = YansWifiChannelHelper::Default();
  YansWifiPhyHelper phy = YansWifiPhyHelper::Default();
  phy.SetChannel (channel.Create ());

  WifiHelper wifi;
  Config::SetDefault("ns3::WifiRemoteStationManager::RtsCtsThreshold",StringValue("1000"));
  
  WifiMacHelper mac;
  Ssid ssid = Ssid ("ns-3-ssid");
  mac.SetType ("ns3::StaWifiMac",
               "Ssid", SsidValue (ssid),
               "ActiveProbing", BooleanValue (false));

  NetDeviceContainer staDevices;
  staDevices = wifi.Install (phy, mac, wifiStaNodes);

  mac.SetType ("ns3::ApWifiMac",
               "Ssid", SsidValue (ssid));

  NetDeviceContainer apDevices;
  apDevices = wifi.Install (phy, mac, wifiApNode);

  wifi.SetStandard (WIFI_PHY_STANDARD_80211ac); // IEEE 802.11ac

  MobilityHelper mobility;
  
  mobility.SetPositionAllocator ("ns3::GridPositionAllocator",
                                 "MinX", DoubleValue (0.0),
                                 "MinY", DoubleValue (0.0),
                                 "DeltaX", DoubleValue (distance),
                                 "DeltaY", DoubleValue (distance),
                                 "GridWidth", UintegerValue (2),
                                 "LayoutType", StringValue ("RowFirst"));

  
  mobility.SetMobilityModel ("ns3::RandomWalk2dMobilityModel",
                             "Bounds", RectangleValue (Rectangle (-50, 50, -50, 50)),"Speed",StringValue ("ns3::UniformRandomVariable[Min="+speed1+"|Max="+speed2+"]"));
  //mobility.SetMobilityModel ("ns3::ConstantPositionMobilityModel");
  mobility.Install (wifiStaNodes);
 
  mobility.SetMobilityModel ("ns3::ConstantPositionMobilityModel"); 
  mobility.Install (wifiApNode);

  InternetStackHelper stack;
  stack.Install (wifiApNode);
  stack.Install (wifiStaNodes);

  Ipv4AddressHelper address;

  address.SetBase ("10.1.1.0", "255.255.255.0");
  address.Assign (staDevices);
  address.Assign (apDevices);

  UdpEchoServerHelper echoServer (9);

  // Instala servidor no AP e cliente em todas as estações 
  // O echo do servidor para este programa está desativado
  ApplicationContainer serverApps = echoServer.Install (wifiApNode.Get(0));
  serverApps.Start (Seconds (1.0));
  serverApps.Stop (Seconds (1.0));

  Ptr<Ipv4> N34 = wifiApNode.Get(0)->GetObject<Ipv4>();
  Ipv4Address N3addr = N34->GetAddress(1,0).GetLocal();

  UdpEchoClientHelper echoClient (N3addr, 9);
  echoClient.SetAttribute ("MaxPackets", UintegerValue (4294967295));  // 2^32 -1 
  echoClient.SetAttribute ("Interval", TimeValue (Seconds (0.00002)));
  echoClient.SetAttribute ("PacketSize", UintegerValue (packet_s));

  ApplicationContainer clientApps;
  clientApps = echoClient.Install (wifiStaNodes);
  clientApps.Start (Seconds (2.0));
  clientApps.Stop (Seconds (20.0));
 
  FlowMonitorHelper flowmon;
  Ptr<FlowMonitor> flowMonitor = flowmon.InstallAll ();

  Simulator::Stop (Seconds (20.0));

  phy.EnablePcapAll ("WIFI", staDevices.Get (0));
  
  pAnim = new AnimationInterface ("wifi-netanim.xml");
  pAnim->SetMaxPktsPerTraceFile(50000000);
  uint32_t resourceId1 = pAnim->AddResource ("/home/aluno/source/netanim-3.108/ap.png");
  pAnim->UpdateNodeImage (nWifi, resourceId1);
  pAnim->UpdateNodeDescription (nWifi, "-----Access Point");
  uint32_t resourceId2 = pAnim->AddResource ("/home/aluno/source/netanim-3.108/sta.png");

  for (uint32_t i=0; i<nWifi; i++){
      pAnim->UpdateNodeImage (i, resourceId2);
      pAnim->UpdateNodeDescription (i, "-----Estação "+std::to_string(i));   
}

  
  std::ostringstream oss;
  oss << "/NodeList/*/$ns3::MobilityModel/CourseChange";
  Config::Connect (oss.str (), MakeCallback (&CourseChange));

  Simulator::Run ();

  // Mostra estatísticas por fluxo
  flowMonitor->CheckForLostPackets ();
  Ptr<Ipv4FlowClassifier> classifier = DynamicCast<Ipv4FlowClassifier> (flowmon.GetClassifier ());
  std::map<FlowId, FlowMonitor::FlowStats> stats = flowMonitor->GetFlowStats ();

  flowMonitor->SerializeToXmlFile("wifi-flowmon.xml", true, true);

  for (std::map<FlowId, FlowMonitor::FlowStats>::const_iterator i = stats.begin (); i != stats.end (); ++i)
{
    Ipv4FlowClassifier::FiveTuple t = classifier->FindFlow (i->first);
    std::cout << "Flow " << i->first - 1 << " (" << t.sourceAddress << " -> " << t.destinationAddress << ")\n";
    std::cout << "  Tx Pacotes: " << i->second.txPackets << "\n";
    std::cout << "  Tx Bytes:   " << i->second.txBytes << "\n";
    std::cout << "  Tx Taxa de bits média:  " << ((i->second.txBytes * 8.0)/((i->second.timeLastTxPacket.GetSeconds()-i->second.timeFirstTxPacket.GetSeconds())))  << " bps\n";
    std::cout << "  Rx Pacotes: " << i->second.rxPackets << "\n";
    std::cout << "  Rx Bytes:   " << i->second.rxBytes << "\n";
    std::cout << "  Rx Taxa de bits média: " << ((i->second.rxBytes * 8.0)/ ((i->second.timeLastRxPacket.GetSeconds()-i->second.timeFirstRxPacket.GetSeconds())))  << " bps\n";
    std::cout << "  Throughput médio (simulação): " << (i->second.rxBytes * 8.0)/20.0 << " bps\n";
    std::cout << "  Atraso médio: " << i->second.delaySum.GetSeconds()/i->second.rxPackets << " s\n";
    std::cout << "  Jitter médio: " << 1000 * (i->second.jitterSum.GetSeconds()/(i->second.rxPackets -1)) << " ms\n";
    std::cout << "  Número de pacotes perdidos: " << i->second.lostPackets << "\n";

}

  Simulator::Destroy ();
  return 0;
}
