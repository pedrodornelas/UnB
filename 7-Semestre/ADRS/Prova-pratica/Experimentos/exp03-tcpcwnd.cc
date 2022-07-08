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
 * Modificado por: Claudia Barenco Abbas 
 */

#include <fstream>
#include <iostream>
#include <string>
#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/applications-module.h"
#include "ns3/gnuplot.h"                          //Para o GnuPlot
#include "ns3/flow-monitor-helper.h"              //Para uso do FlowMonitor
#include "ns3/flow-monitor.h"
#include "ns3/ipv4-flow-classifier.h"             //Para classificador do fluxo

using namespace ns3;

NS_LOG_COMPONENT_DEFINE ("tcpcwnd");

// =====================================================================================
//
//         node 0                 node 1
//   +----------------+    +----------------+
//   |    ns-3 TCP    |    |    ns-3 TCP    |
//   +----------------+    +----------------+
//   |    10.1.1.1    |    |    10.1.1.2    |
//   +----------------+    +----------------+
//   | point-to-point |    | point-to-point |
//   +----------------+    +----------------+
//           |                     |
//           +---------------------+
//                5 Mbps, 2 ms
//
// =====================================================================================
// Aplicação on-off para gerar fluxos 
// Cria-se um socket e instala-se um rastreamento e depois instala-se em um nó origem 
// Mostra mensagens quando pacotes são descartados 
// =====================================================================================
//
// Tipos de protocolo TCP:
//
// TcpHybla, TcpHighSpeed, TcpHtcp, TcpScalable, TcpVeno, 
// TcpBic, TcpYeah, TcpIllinois, TcpWestwood, TcpWestwoodPlus, TcpLedbat, 
// TcpLp, TcpNewReno
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

static void
RxDrop (Ptr<const Packet> p)
{
  std::cout << "Pacote descartado em " << Simulator::Now ().GetSeconds () << " s\n";
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
  std::cout << "Simulando...\n";
  uint16_t MinRto = 1000;          // Tempo mínimo de espera para retransmissões em milisegundos
  uint16_t runtime = 100;          // Tempo de simulação em segundos
  uint16_t tcpSegmentSize = 512;  // Tamanho de segmentos TCP em bytes
  uint16_t delAck = 1;             // Número pacotes para esperar antes antes do ACK

  // Parâmetros que podem ser alterados na linha de comando
  CommandLine cmd;
  cmd.AddValue ("runtime", "Tempo de simulação em segundos", runtime);
  cmd.AddValue ("tcpSegmentSize", "Tamanho segmento TCP", tcpSegmentSize);
  cmd.AddValue ("MinRto", "Mínimo Tempo Espera para Retransmissões", MinRto);
  cmd.Parse (argc, argv);

  // Configuração do TCP
  Config::SetDefault ("ns3::TcpL4Protocol::SocketType", StringValue ("ns3::TcpNewReno"));
  Config::SetDefault ("ns3::TcpSocket::SegmentSize", UintegerValue (tcpSegmentSize));
  Config::SetDefault ("ns3::TcpSocket::DelAckCount", UintegerValue (delAck));
  Config::SetDefault ("ns3::TcpSocketBase::MinRto", TimeValue (MilliSeconds (MinRto))); 

  // Criação da topologia

  NodeContainer nodes;
  nodes.Create (2);

  PointToPointHelper pointToPoint;
  pointToPoint.SetDeviceAttribute ("DataRate", StringValue ("5Mbps"));
  pointToPoint.SetChannelAttribute ("Delay", StringValue ("2ms"));

  NetDeviceContainer devices;
  devices = pointToPoint.Install (nodes);

  // Erro no canal
  Ptr<RateErrorModel> em = CreateObject<RateErrorModel> ();
  Ptr<UniformRandomVariable> uv = CreateObject<UniformRandomVariable> ();
  em->SetRandomVariable (uv);
  em->SetAttribute ("ErrorRate", DoubleValue (0.0001));
  devices.Get (1)->SetAttribute ("ReceiveErrorModel", PointerValue (em));

 devices.Get (1)->TraceConnectWithoutContext ("PhyRxDrop", MakeCallback (&RxDrop));

  // Pilha TCP/IP
  InternetStackHelper stack;
  stack.Install (nodes);

  // Endereçamento IP
  Ipv4AddressHelper address;
  address.SetBase ("10.1.1.0", "255.255.255.252");
  Ipv4InterfaceContainer interfaces = address.Assign (devices);


  // Servidor
  uint16_t sinkPort = 8080;
  Address sinkAddress (InetSocketAddress (interfaces.GetAddress (1), sinkPort));
  PacketSinkHelper packetSinkHelper ("ns3::TcpSocketFactory", InetSocketAddress (Ipv4Address::GetAny (), sinkPort));
  ApplicationContainer sinkApps = packetSinkHelper.Install (nodes.Get (1));
  sinkApps.Start (Seconds (0.));
  sinkApps.Stop (Seconds (runtime));


  // Cliente
  Ptr<Socket> ns3TcpSocket = Socket::CreateSocket (nodes.Get (0), TcpSocketFactory::GetTypeId ());
  ns3TcpSocket->TraceConnectWithoutContext ("CongestionWindow", MakeCallback (&CwndChange));

  Ptr<MyApp> app = CreateObject<MyApp> ();
  app->Setup (ns3TcpSocket, sinkAddress, 1040, 10000000, DataRate ("5Mbps"));
  nodes.Get (0)->AddApplication (app);
  app->SetStartTime (Seconds (1.));
  app->SetStopTime (Seconds (runtime));

 
  // Configura o traçado (pcap) para WireShark
  pointToPoint.EnablePcapAll ("tcpcwnd");

  // Instala FlowMonitor em todos os nós 
  FlowMonitorHelper flowmon;
  Ptr<FlowMonitor> monitor = flowmon.InstallAll ();
  
  Simulator::Stop (Seconds (runtime));

  Simulator::Run ();

  monitor->CheckForLostPackets ();

  // Escreve estatísticas dos fluxos em um arquivo XML 
  monitor->SerializeToXmlFile("tcpcwnd.xml", true, true);
  
  // Mostra estatísticas por fluxo
  Ptr<Ipv4FlowClassifier> classifier = DynamicCast<Ipv4FlowClassifier> (flowmon.GetClassifier ());
  std::map<FlowId, FlowMonitor::FlowStats> stats = monitor->GetFlowStats ();
  for (std::map<FlowId, FlowMonitor::FlowStats>::const_iterator i = stats.begin (); i != stats.end (); ++i)
  {
	Ipv4FlowClassifier::FiveTuple t = classifier->FindFlow (i->first);
    std::cout << "Flow " << i->first << " (" << t.sourceAddress << ":" << t.sourcePort << " -> "<< t.destinationAddress << ":" << t.destinationPort << ")\n";
    std::cout << "  Tx Pacotes: " << i->second.txPackets << "\n";
    std::cout << "  Tx Bytes:   " << i->second.txBytes << "\n";
    std::cout << "  Tx Taxa de bits média:  " << ((i->second.txBytes * 8.0)/((i->second.timeLastTxPacket.GetSeconds()-i->second.timeFirstTxPacket.GetSeconds())))  << " bps\n";
    std::cout << "  Rx Pacotes: " << i->second.rxPackets << "\n";
    std::cout << "  Rx Bytes:   " << i->second.rxBytes << "\n";
    std::cout << "  Rx Taxa de bits média: " << ((i->second.rxBytes * 8.0)/ ((i->second.timeLastRxPacket.GetSeconds()-i->second.timeFirstRxPacket.GetSeconds())))  << " bps\n";
    std::cout << "  Throughput médio (simulação): " << (i->second.rxBytes * 8.0)/runtime << " bps\n";
    std::cout << "  Atraso médio: " << i->second.delaySum.GetSeconds()/i->second.rxPackets << " s\n";
    std::cout << "  Jitter médio: " << 1000 * (i->second.jitterSum.GetSeconds()/(i->second.rxPackets -1)) << " ms\n";
    std::cout << "  Número de pacotes perdidos: " << i->second.lostPackets << "\n";
	}

  // Plota gráfico da janela de congestiontamento
  Create2DPlotFile(dataset, "tcpcwnd", "Gráfico de Mudança CWND", "Tamanho CWND", "Tempo Simulação", "Tamanho CWND (bytes)",
  "[0:100]", "[0:8000]");

	Simulator::Destroy ();

  return 0;
}

