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


NS_LOG_COMPONENT_DEFINE ("questao3");

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

class MyApp : public Application 
{
public:

  MyApp ();
  virtual ~MyApp();

  void Setup (Ptr<Socket> socket, Address address, uint32_t packetSize, uint32_t nPackets, DataRate dataRate);

private:
  virtual void StartApplication (void);
  virtual void StopApplication (void);

  void ScheduleTx (void);
  void SendPacket (void);

  Ptr<Socket>     m_socket;
  Address         m_peer;
  uint32_t        m_packetSize;
  uint32_t        m_nPackets;
  DataRate        m_dataRate;
  EventId         m_sendEvent;
  bool            m_running;
  uint32_t        m_packetsSent;
};

MyApp::MyApp ()
  : m_socket (0), 
    m_peer (), 
    m_packetSize (0), 
    m_nPackets (0), 
    m_dataRate (0), 
    m_sendEvent (), 
    m_running (false), 
    m_packetsSent (0)
{
}

MyApp::~MyApp()
{
  m_socket = 0;
}

void
MyApp::Setup (Ptr<Socket> socket, Address address, uint32_t packetSize, uint32_t nPackets, DataRate dataRate)
{
  m_socket = socket;
  m_peer = address;
  m_packetSize = packetSize;
  m_nPackets = nPackets;
  m_dataRate = dataRate;
}

void
MyApp::StartApplication (void)
{
  m_running = true;
  m_packetsSent = 0;
  m_socket->Bind ();
  m_socket->Connect (m_peer);
  SendPacket ();
}

void 
MyApp::StopApplication (void)
{
  m_running = false;

  if (m_sendEvent.IsRunning ())
    {
      Simulator::Cancel (m_sendEvent);
    }

  if (m_socket)
    {
      m_socket->Close ();
    }
}

void 
MyApp::SendPacket (void)
{
  Ptr<Packet> packet = Create<Packet> (m_packetSize);
  m_socket->Send (packet);

  if (++m_packetsSent < m_nPackets)
    {
      ScheduleTx ();
    }
}

void 
MyApp::ScheduleTx (void)
{
  if (m_running)
    {
      Time tNext (Seconds (m_packetSize * 8 / static_cast<double> (m_dataRate.GetBitRate ())));
      m_sendEvent = Simulator::Schedule (tNext, &MyApp::SendPacket, this);
    }
}

std::ofstream meuarquivo("tcpcwnd", std::fstream::app); // Arquivo que guardará informação tempo simulação e tamanho janela 
Gnuplot2dDataset dataset; //Conjunto de Dados para o gnuplot

static void
CwndChange (uint32_t oldCwnd, uint32_t newCwnd)
{
  meuarquivo << Simulator::Now ().GetSeconds () << " " << newCwnd << std::endl;  
  dataset.Add (Simulator::Now ().GetSeconds (), newCwnd);      
}

int 
main (int argc, char *argv[])
{
  

  saida.open("/home/ns3/ns-allinone-3.33/ns-3.33/questao3.csv");


  // Parse de Comandos
  std::string DdataRate="10Mbps";
  std::string Delay="2ms";

  std::string DataRateAccess = "10Mbps";
  std::string DelayAccess = "1ms";

  uint32_t time = 10;
  uint32_t nPackets = 1000000;
  uint32_t MaxPacketSize = 1024;
  CommandLine cmd;

  // Parâmetros TCP
  uint16_t MinRto = 1000;          // Tempo mínimo de espera para retransmissões em milisegundos
  //uint16_t runtime = 100;          // Tempo de simulação em segundos
  uint16_t tcpSegmentSize = 512;  // Tamanho de segmentos TCP em bytes
  uint16_t delAck = 1;             // Número pacotes para esperar antes antes do ACK

  // Alteracao do Numero de pacotes a serem transmitidos
  cmd.AddValue("nPackets","Numero de pacotes para enviar no echo.",nPackets);

  // Alteracao da Taxa de Dados na Camada de Enlace  
  cmd.AddValue("DataRate","Taxa de dados no enlace Ponto a Ponto Backbone.",DdataRate);
  cmd.AddValue("Delay","Atraso de Propagacao no enlace Ponto a Ponto Backbone.",Delay);
  cmd.AddValue("Time","Tempo de Simulacao.",time);
  cmd.AddValue("MaxPacketSize","Tamanho maximo dos pacotes.",MaxPacketSize);

  cmd.Parse (argc, argv);

  // Configuração do TCP
  Config::SetDefault ("ns3::TcpL4Protocol::SocketType", TypeIdValue (TypeId::LookupByName ("ns3::TcpVegas")));
  Config::SetDefault ("ns3::TcpSocket::SegmentSize", UintegerValue (tcpSegmentSize));
  Config::SetDefault ("ns3::TcpSocket::DelAckCount", UintegerValue (delAck));
  Config::SetDefault ("ns3::TcpSocketBase::MinRto", TimeValue (MilliSeconds (MinRto)));


  Time::SetResolution (Time::NS); 

  // Cria os nos e roteadores
  NodeContainer n0,n1,n2,n3,R0,R1;
  n0.Create(1); //no 0 esquerda
  n1.Create(1); //no 1 esquerda
  n2.Create(1); //no 0 direita
  n3.Create(1); //no 1 direita

  R0.Create(1);
  R1.Create(1);

  // Define os canais
  PointToPointHelper accessLink0, accessLink1, bottleneckLink, accessLink2, accessLink3;

  accessLink0.SetDeviceAttribute ("DataRate", StringValue (DataRateAccess));
  accessLink0.SetChannelAttribute ("Delay", StringValue (DelayAccess));

  accessLink1.SetDeviceAttribute ("DataRate", StringValue (DataRateAccess));
  accessLink1.SetChannelAttribute ("Delay", StringValue (DelayAccess));

  bottleneckLink.SetDeviceAttribute ("DataRate", StringValue(DdataRate));
  bottleneckLink.SetChannelAttribute ("Delay", StringValue(Delay));

  accessLink2.SetDeviceAttribute ("DataRate", StringValue (DataRateAccess));
  accessLink2.SetChannelAttribute ("Delay", StringValue (DelayAccess));

  accessLink3.SetDeviceAttribute ("DataRate", StringValue (DataRateAccess));
  accessLink3.SetChannelAttribute ("Delay", StringValue (DelayAccess));

  // Define os devices -> instalacao dos enlaces nos nos
  NetDeviceContainer devicesAccessLink0, devicesAccessLink1, devicesBottleneckLink, devicesAccessLink2, devicesAccessLink3;

  devicesAccessLink0 = accessLink0.Install(n0.Get(0), R0.Get(0));
  devicesAccessLink1 = accessLink1.Install(n1.Get(0), R0.Get(0));

  devicesBottleneckLink = bottleneckLink.Install(R0.Get(0), R1.Get(0));
  
  devicesAccessLink2 = accessLink2.Install(R1.Get(0), n2.Get(0));
  devicesAccessLink3 = accessLink3.Install(R1.Get(0), n3.Get(0));

  InternetStackHelper stack;
  stack.InstallAll();

  // Cria interfaces -> Atribuicao dos enderecos IP em devices
  Ipv4AddressHelper address;
  address.SetBase ("10.1.0.0", "255.255.255.253");
  Ipv4InterfaceContainer interfacesAccess0 = address.Assign (devicesAccessLink0);
  address.SetBase ("10.1.0.4", "255.255.255.253");
  Ipv4InterfaceContainer interfacesAccess1 = address.Assign (devicesAccessLink1);

  address.SetBase ("10.3.0.0", "255.255.255.0");
  Ipv4InterfaceContainer interfacesBottleneck = address.Assign (devicesBottleneckLink);
  
  address.SetBase ("10.2.0.0", "255.255.255.253");
  Ipv4InterfaceContainer interfacesAccess2 = address.Assign (devicesAccessLink2);
  address.SetBase ("10.2.0.4", "255.255.255.253");
  Ipv4InterfaceContainer interfacesAccess3 = address.Assign (devicesAccessLink3);
  
  Ipv4GlobalRoutingHelper::PopulateRoutingTables ();

  //Porta das aplicações em ambos servidores são iguais, utilizarei a mesma variável
  uint16_t port_UDP = 4000;

  // Cria aplicacao servidora UDP no no 2(no 0 direita), porta 4444
  UdpServerHelper server1 (port_UDP);
  ApplicationContainer apps1 = server1.Install (n2.Get (0));
  apps1.Start (Seconds (1.0));
  apps1.Stop (Seconds (9.0));

  // Cria aplicacao cliente no no 0 (no 0 esquerda)
  Time interPacketInterval = Seconds (0.05);
  uint32_t maxPacketCount = 1000000;

  UdpEchoClientHelper client1 (interfacesAccess2.GetAddress (1), port_UDP);
  client1.SetAttribute ("MaxPackets", UintegerValue (maxPacketCount));
  client1.SetAttribute ("Interval", TimeValue (interPacketInterval));
  client1.SetAttribute ("PacketSize", UintegerValue (MaxPacketSize));
  apps1 = client1.Install (n0.Get (0));
  apps1.Start (Seconds (5.0));
  apps1.Stop (Seconds (7.0));


  // Servidor TCP
  uint16_t sinkPort = 8080;
  Address sinkAddress (InetSocketAddress (interfacesAccess3.GetAddress (1), sinkPort));
  PacketSinkHelper packetSinkHelper ("ns3::TcpSocketFactory", InetSocketAddress (Ipv4Address::GetAny (), sinkPort));
  ApplicationContainer sinkApps = packetSinkHelper.Install (n3.Get (0));
  sinkApps.Start (Seconds (0.0));
  sinkApps.Stop (Seconds (10.0));

  // Cliente TCP
  Ptr<Socket> ns3TcpSocket = Socket::CreateSocket (n1.Get (0), TcpSocketFactory::GetTypeId ());
  ns3TcpSocket->TraceConnectWithoutContext ("CongestionWindow", MakeCallback (&CwndChange));

  Ptr<MyApp> app = CreateObject<MyApp> ();
  app->Setup (ns3TcpSocket, sinkAddress, 1040, 10000000, DataRate ("5Mbps"));
  n1.Get (0)->AddApplication (app);
  app->SetStartTime (Seconds (1.0));
  app->SetStopTime (Seconds (8.0));


  // P2P TX Queue Tracing
  Config::ConnectWithoutContext("/NodeList/4/DeviceList/*/$ns3::PointToPointNetDevice/TxQueue/PacketsInQueue", MakeCallback(&P2PTXQueueNPackets));

  // Habilita rastreamento de trafego em formato ASCII
  AsciiTraceHelper ascii;
  bottleneckLink.EnableAsciiAll(ascii.CreateFileStream("questao3.tr"));

  // Habilita rastreamento de trafego em formato PCAP
  bottleneckLink.EnablePcap ("questao3", devicesBottleneckLink.Get(0));
  // bottleneckLink.EnablePcap ("N3UDPGargalo", devicesAccessLink1.Get(0));

  // Instala FlowMonitor em todos os nos 
  Ptr<FlowMonitor> flowMonitor;
  FlowMonitorHelper flowHelper;
  flowMonitor = flowHelper.InstallAll ();

  // Define tempo de simulacao 
  Simulator::Stop (time);

  // Executa simulacao
  Simulator::Run ();

  flowMonitor->CheckForLostPackets ();

  // Escreve estatisticas dos fluxos em um arquivo XML 
  flowMonitor->SerializeToXmlFile("questao3.xml", true, true);

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

  Create2DPlotFile (dataset1, "questao3", "Tamanho da Fila x Tempo de Simulacao", "Pacotes na fila", "Tempo de Simulacao (s)",
  "Numero de pacotes na fila", "[0:100]", "[0:100]");

  // Plota gráfico da janela de congestiontamento
  Create2DPlotFile(dataset, "tcpcwnd", "Gráfico de Mudança CWND", "Tamanho CWND", "Tempo Simulação", "Tamanho CWND (bytes)",
  "[0:10]", "[0:20000]");
  
  Simulator::Destroy ();

  saida.close();

  return 0;
}
