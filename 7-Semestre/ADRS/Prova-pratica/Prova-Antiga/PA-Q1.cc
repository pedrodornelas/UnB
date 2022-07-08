/*
Aluno: Pedro Henrique Dornelas Almeida
Matricula: 18/0108140
*/

#include <fstream>
#include <vector>
#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/applications-module.h"
#include "ns3/flow-monitor-helper.h"              //Para uso do FlowMonitor
#include "ns3/flow-monitor.h"
#include "ns3/ipv4-flow-classifier.h"             //Para classificador do fluxo
#include "ns3/gnuplot.h"                          //Para GnuPlot
#include "ns3/ipv4-l3-protocol.h"
#include "ns3/traffic-control-module.h"
      

using namespace ns3;


NS_LOG_COMPONENT_DEFINE ("questao1");

Gnuplot2dDataset dataset1;

std::ofstream saida;

void
P2PTXQueueNPackets(uint32_t oldValue, uint32_t newValue){
  double time = Simulator::Now().GetSeconds();

  dataset1.Add(time ,newValue);
  std::cout<< "Pacotes na fila: " << oldValue<< "->" << newValue << "\n";

  saida << time << ";" << oldValue<< ";" << newValue << "\n";

}

void 
Create2DPlotFile (Gnuplot2dDataset GnuDataset, std::string fileName, std::string plotTitle, std::string dataTitle, std::string xLegend,
std::string yLegend, std::string xRange, std::string yRange) {
  std::string fileNameWithNoExtension = fileName;
  std::string graphicsFileName  = fileNameWithNoExtension + ".png";
  std::string plotFileName = fileNameWithNoExtension + ".plt";

  // Instantiate the plot and set its title.
  Gnuplot plot (graphicsFileName);
  plot.SetTitle (plotTitle);

  // Make the graphics file, which the plot file will create when it
  // is used with Gnuplot, be a PNG file.
  plot.SetTerminal ("png");

  // Set the labels for each axis.
  plot.SetLegend (xLegend, yLegend);

  // Set the range for the x axis.
  plot.AppendExtra ("set xrange "+xRange);

  // Set the range for the y axis.
  plot.AppendExtra ("set yrange "+yRange);

  // Instantiate the dataset1, set its title, and make the points be
  // plotted along with connecting lines.
  GnuDataset.SetTitle (dataTitle);
  GnuDataset.SetStyle (Gnuplot2dDataset::STEPS);

  // Add the dataset1 to the plot.
  plot.AddDataset (GnuDataset);

  // Open the plot file.
  std::ofstream plotFile (plotFileName.c_str());

  // Write the plot file.
  plot.GenerateOutput (plotFile);

  // Close the plot file.
  plotFile.close ();
}

int
main (int argc, char *argv[])
{
  

  saida.open("/home/ns3/ns-allinone-3.33/ns-3.33/questao1.csv");


  // Parse de Comandos
  std::string DataRate="90kbps";
  std::string Delay="3ms";

  std::string DataRateAccess = "100kbps";
  std::string DelayAccess = "2ms";

  uint32_t time = 10;
  uint32_t nPackets = 1000000;
  uint32_t MaxPacketSize = 1024;
  CommandLine cmd;  

  // Alteracao do Numero de pacotes a serem transmitidos
  cmd.AddValue("nPackets","Numero de pacotes para enviar no echo.",nPackets);

  // Alteracao da Taxa de Dados na Camada de Enlace  
  cmd.AddValue("DataRate","Taxa de dados no enlace Ponto a Ponto Backbone.",DataRate);
  cmd.AddValue("Delay","Atraso de Propagacao no enlace Ponto a Ponto Backbone.",Delay);
  cmd.AddValue("Time","Tempo de Simulacao.",time);
  cmd.AddValue("MaxPacketSize","Tamanho maximo dos pacotes.",MaxPacketSize);

  cmd.Parse (argc, argv);

  Time::SetResolution (Time::NS); 

  // Cria os nos e roteadores
  NodeContainer n0,n1,n2,n3,n4,n5,R0,R1;
  n0.Create(1);
  n1.Create(1);
  n2.Create(1);
  n3.Create(1);
  n4.Create(1);
  n5.Create(1);

  R0.Create(1);
  R1.Create(1);

  // Define os canais
  PointToPointHelper accessLink0, accessLink1, accessLink2, bottleneckLink, accessLink3, accessLink4, accessLink5;

  accessLink0.SetDeviceAttribute ("DataRate", StringValue (DataRateAccess));
  accessLink0.SetChannelAttribute ("Delay", StringValue (DelayAccess));

  accessLink1.SetDeviceAttribute ("DataRate", StringValue (DataRateAccess));
  accessLink1.SetChannelAttribute ("Delay", StringValue (DelayAccess));

  accessLink2.SetDeviceAttribute ("DataRate", StringValue (DataRateAccess));
  accessLink2.SetChannelAttribute ("Delay", StringValue (DelayAccess));

  bottleneckLink.SetDeviceAttribute ("DataRate", StringValue(DataRate));
  bottleneckLink.SetChannelAttribute ("Delay", StringValue(Delay));

  accessLink3.SetDeviceAttribute ("DataRate", StringValue (DataRateAccess));
  accessLink3.SetChannelAttribute ("Delay", StringValue (DelayAccess));

  accessLink4.SetDeviceAttribute ("DataRate", StringValue (DataRateAccess));
  accessLink4.SetChannelAttribute ("Delay", StringValue (DelayAccess));

  accessLink5.SetDeviceAttribute ("DataRate", StringValue (DataRateAccess));
  accessLink5.SetChannelAttribute ("Delay", StringValue (DelayAccess));

  // Define os devices -> instalacao dos enlaces nos nos
  NetDeviceContainer devicesAccessLink0, devicesAccessLink1, devicesAccessLink2, devicesBottleneckLink, devicesAccessLink3, devicesAccessLink4, devicesAccessLink5;

  devicesAccessLink0 = accessLink0.Install(n0.Get(0), R0.Get(0));
  devicesAccessLink1 = accessLink1.Install(n1.Get(0), R0.Get(0));
  devicesAccessLink2 = accessLink2.Install(n2.Get(0), R0.Get(0));

  devicesBottleneckLink = bottleneckLink.Install(R0.Get(0), R1.Get(0));
  
  devicesAccessLink3 = accessLink3.Install(R1.Get(0), n3.Get(0));
  devicesAccessLink4 = accessLink4.Install(R1.Get(0), n4.Get(0));
  devicesAccessLink5 = accessLink5.Install(R1.Get(0), n5.Get(0));

  InternetStackHelper stack;
  stack.InstallAll();

  // Cria interfaces -> Atribuicao dos enderecos IP em devices
  Ipv4AddressHelper address;
  address.SetBase ("10.0.1.0", "255.255.255.253");
  Ipv4InterfaceContainer interfacesAccess0 = address.Assign (devicesAccessLink0);
  address.SetBase ("10.0.1.4", "255.255.255.253");
  Ipv4InterfaceContainer interfacesAccess1 = address.Assign (devicesAccessLink1);
  address.SetBase ("10.0.1.8", "255.255.255.253");
  Ipv4InterfaceContainer interfacesAccess2 = address.Assign (devicesAccessLink2);

  address.SetBase ("10.0.3.0", "255.255.255.0");
  Ipv4InterfaceContainer interfacesBottleneck = address.Assign (devicesBottleneckLink);
  
  address.SetBase ("10.0.2.0", "255.255.255.253");
  Ipv4InterfaceContainer interfacesAccess3 = address.Assign (devicesAccessLink3);
  address.SetBase ("10.0.2.4", "255.255.255.253");
  Ipv4InterfaceContainer interfacesAccess4 = address.Assign (devicesAccessLink4);
  address.SetBase ("10.0.2.8", "255.255.255.253");
  Ipv4InterfaceContainer interfacesAccess5 = address.Assign (devicesAccessLink5);
  
  Ipv4GlobalRoutingHelper::PopulateRoutingTables ();

  //Porta das aplicações em ambos servidores são iguais, utilizarei a mesma variável
  uint16_t port = 4444;

  // Cria aplicacao servidora no no 3, porta 4444
  UdpServerHelper server1 (port);
  ApplicationContainer apps1 = server1.Install (n3.Get (0));
  apps1.Start (Seconds (0.0));
  apps1.Stop (Seconds (time));

  // Cria aplicacao servidora no no 4, porta 4444
  UdpServerHelper server2 (port);
  ApplicationContainer apps2 = server2.Install (n4.Get (0));
  apps2.Start (Seconds (0.0));
  apps2.Stop (Seconds (time));

  // Cria aplicacao servidora no no 5, porta 4444
  UdpServerHelper server3 (port);
  ApplicationContainer apps3 = server3.Install (n5.Get (0));
  apps3.Start (Seconds (0.0));
  apps3.Stop (Seconds (time));
  
  // Cria aplicacao cliente no no 0
  Time interPacketInterval = Seconds (0.187);
  uint32_t maxPacketCount = nPackets;

  UdpEchoClientHelper client1 (interfacesAccess3.GetAddress (1), port);
  client1.SetAttribute ("MaxPackets", UintegerValue (maxPacketCount));
  client1.SetAttribute ("Interval", TimeValue (interPacketInterval));
  client1.SetAttribute ("PacketSize", UintegerValue (MaxPacketSize));
  apps1 = client1.Install (n0.Get (0));
  apps1.Start (Seconds (0.1));
  apps1.Stop (Seconds (time));

  // Cria aplicacao cliente no no 1

  UdpEchoClientHelper client2 (interfacesAccess4.GetAddress (1), port);
  client2.SetAttribute ("MaxPackets", UintegerValue (maxPacketCount));
  client2.SetAttribute ("Interval", TimeValue (interPacketInterval));
  client2.SetAttribute ("PacketSize", UintegerValue (MaxPacketSize));
  apps2 = client2.Install (n1.Get (0));
  apps2.Start (Seconds (0.1));
  apps2.Stop (Seconds (time));

  // Cria aplicacao cliente no no 2

  UdpEchoClientHelper client3 (interfacesAccess5.GetAddress (1), port);
  client3.SetAttribute ("MaxPackets", UintegerValue (maxPacketCount));
  client3.SetAttribute ("Interval", TimeValue (interPacketInterval));
  client3.SetAttribute ("PacketSize", UintegerValue (MaxPacketSize));
  apps3 = client3.Install (n2.Get (0));
  apps3.Start (Seconds (0.1));
  apps3.Stop (Seconds (time));

  // P2P TX Queue Tracing
  Config::ConnectWithoutContext("/NodeList/6/DeviceList/*/$ns3::PointToPointNetDevice/TxQueue/PacketsInQueue", MakeCallback(&P2PTXQueueNPackets));

  // Habilita rastreamento de trafego em formato ASCII
  AsciiTraceHelper ascii;
  bottleneckLink.EnableAsciiAll(ascii.CreateFileStream("questao1.tr"));

  // Habilita rastreamento de trafego em formato PCAP
  bottleneckLink.EnablePcap ("questao1", devicesBottleneckLink.Get(0));
  // bottleneckLink.EnablePcap ("N3UDPGargalo", devicesAccessLink1.Get(0));

  // Instala FlowMonitor em todos os nos 
  Ptr<FlowMonitor> flowMonitor;
  FlowMonitorHelper flowHelper;
  flowMonitor = flowHelper.InstallAll ();

  // Define tempo de simulacao 
  Simulator::Stop (Seconds (time));

  // Executa simulacao
  Simulator::Run ();

  flowMonitor->CheckForLostPackets ();

  // Escreve estatisticas dos fluxos em um arquivo XML 
  flowMonitor->SerializeToXmlFile("questao1.xml", true, true);

  // Mostra estatisticas por fluxo
  Ptr<Ipv4FlowClassifier> classifier = DynamicCast<Ipv4FlowClassifier> (flowHelper.GetClassifier ());
  std::map<FlowId, FlowMonitor::FlowStats> stats = flowMonitor->GetFlowStats ();
  
  for (std::map<FlowId, FlowMonitor::FlowStats>::const_iterator i = stats.begin (); i != stats.end (); ++i)
    {
      Ipv4FlowClassifier::FiveTuple t = classifier->FindFlow (i->first);
      std::cout << "Flow " << i->first << " (" << t.sourceAddress << ":" << t.sourcePort << " -> "<< t.destinationAddress << ":" << t.destinationPort << ")\n";
      std::cout << "  Tx Pacotes: " << i->second.txPackets << "\n";
      std::cout << "  Tx Bytes:   " << i->second.txBytes << "\n";
      std::cout << "  Tx Taxa de bits media:  " << ((i->second.txBytes * 8.0)/((i->second.timeLastTxPacket.GetSeconds()-i->second.timeFirstTxPacket.GetSeconds())))  << " bps\n";
      std::cout << "  Rx Pacotes: " << i->second.rxPackets << "\n";
      std::cout << "  Rx Bytes:   " << i->second.rxBytes << "\n";
      std::cout << "  Rx Taxa de bits media: " << ((i->second.rxBytes * 8.0)/ ((i->second.timeLastRxPacket.GetSeconds()-i->second.timeFirstRxPacket.GetSeconds())))  << " bps\n";
      std::cout << "  Throughput medio (simulacao): " << (i->second.rxBytes * 8.0)/time << " bps\n";
      std::cout << "  Atraso medio: " << i->second.delaySum.GetSeconds()/i->second.rxPackets << " s\n";
      std::cout << "  Jitter medio: " << 1000 * (i->second.jitterSum.GetSeconds()/(i->second.rxPackets -1)) << " ms\n";
      std::cout << "  Numero de pacotes perdidos: " << i->second.lostPackets << "\n";

    }

  Create2DPlotFile (dataset1, "questao1", "Tamanho da Fila x Tempo de Simulacao", "Pacotes na fila", "Tempo de Simulacao (s)",
  "Numero de pacotes na fila", "[0:100]", "[0:100]");
  
  Simulator::Destroy ();

  saida.close();

  return 0;
}
