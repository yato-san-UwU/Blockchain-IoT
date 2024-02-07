#include "ns3/core-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/network-module.h"
#include "ns3/applications-module.h"
#include "ns3/mobility-module.h"
#include "ns3/internet-module.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cassert>
#include "ns3/netanim-module.h"
#include "ns3/animation-interface.h"



using namespace ns3;

NS_LOG_COMPONENT_DEFINE ("projet");

void Envoyer (Ptr<Socket> sock, Ipv4Address dstaddr, uint16_t port, uint16_t i);

void Recevoir_N0 (Ptr<Socket> socket);
void Recevoir_N1 (Ptr<Socket> socket);
void Recevoir_N2 (Ptr<Socket> socket);
void Recevoir_N3 (Ptr<Socket> socket);
void Recevoir_N4 (Ptr<Socket> socket);
void Recevoir_N5 (Ptr<Socket> socket);

int main(){

  LogComponentEnable ("projet", LOG_LEVEL_INFO);
/*   LogComponentEnable ("UdpEchoClientApplication", LOG_LEVEL_INFO);
  LogComponentEnable ("UdpEchoServerApplication", LOG_LEVEL_INFO); */
 
  //p2p 1
  NodeContainer p2pNodes1;
  p2pNodes1.Create (2);

  PointToPointHelper pointToPoint1;
  pointToPoint1.SetDeviceAttribute ("DataRate", StringValue ("5Mbps"));
  pointToPoint1.SetChannelAttribute ("Delay", StringValue ("2ms"));

  NetDeviceContainer p2pDevices1;
  p2pDevices1 = pointToPoint1.Install (p2pNodes1);

  //p2p 2
  NodeContainer p2pNodes2;
  p2pNodes2.Add(p2pNodes1.Get(0));
  p2pNodes2.Create (1);

  PointToPointHelper pointToPoint2;
  pointToPoint2.SetDeviceAttribute ("DataRate", StringValue ("5Mbps"));
  pointToPoint2.SetChannelAttribute ("Delay", StringValue ("2ms"));

  NetDeviceContainer p2pDevices2;
  p2pDevices2 = pointToPoint2.Install (p2pNodes2);

  //p2p 3
  NodeContainer p2pNodes3;
  p2pNodes3.Add(p2pNodes1.Get(0));
  p2pNodes3.Create (1);

  PointToPointHelper pointToPoint3;
  pointToPoint3.SetDeviceAttribute ("DataRate", StringValue ("5Mbps"));
  pointToPoint3.SetChannelAttribute ("Delay", StringValue ("2ms"));

  NetDeviceContainer p2pDevices3;
  p2pDevices3 = pointToPoint3.Install (p2pNodes3);

  //p2p 4
  NodeContainer p2pNodes4;
  p2pNodes4.Add(p2pNodes1.Get(0));
  p2pNodes4.Create (1);

  PointToPointHelper pointToPoint4;
  pointToPoint4.SetDeviceAttribute ("DataRate", StringValue ("5Mbps"));
  pointToPoint4.SetChannelAttribute ("Delay", StringValue ("2ms"));

  NetDeviceContainer p2pDevices4;
  p2pDevices4 = pointToPoint4.Install (p2pNodes4);

  //p2p 5
  NodeContainer p2pNodes5;
  p2pNodes5.Add(p2pNodes1.Get(0));
  p2pNodes5.Create (1);

  PointToPointHelper pointToPoint5;
  pointToPoint5.SetDeviceAttribute ("DataRate", StringValue ("5Mbps"));
  pointToPoint5.SetChannelAttribute ("Delay", StringValue ("2ms"));

  NetDeviceContainer p2pDevices5;
  p2pDevices5 = pointToPoint5.Install (p2pNodes5);


  InternetStackHelper stack;

  stack.Install(p2pNodes1);
  stack.Install(p2pNodes2.Get(1));
  stack.Install(p2pNodes3.Get(1));
  stack.Install(p2pNodes4.Get(1));
  stack.Install(p2pNodes5.Get(1));


  //@ IP
  Ipv4AddressHelper address;

  address.SetBase ("10.1.1.0", "255.255.255.0");
  Ipv4InterfaceContainer p2pInterfaces1;
  p2pInterfaces1 = address.Assign (p2pDevices1); 

  address.SetBase ("10.1.2.0", "255.255.255.0");
  Ipv4InterfaceContainer p2pInterfaces2;
  p2pInterfaces2 = address.Assign (p2pDevices2); 

  address.SetBase ("10.1.3.0", "255.255.255.0");
  Ipv4InterfaceContainer p2pInterfaces3;
  p2pInterfaces3 = address.Assign (p2pDevices3); 

  address.SetBase ("10.1.4.0", "255.255.255.0");
  Ipv4InterfaceContainer p2pInterfaces4;
  p2pInterfaces4 = address.Assign (p2pDevices4); 

  address.SetBase ("10.1.5.0", "255.255.255.0");
  Ipv4InterfaceContainer p2pInterfaces5;
  p2pInterfaces5 = address.Assign (p2pDevices5); 


// app socket

  Ptr<Socket> N0 = Socket::CreateSocket (p2pNodes1.Get (0), TypeId::LookupByName ("ns3::UdpSocketFactory"));
  uint16_t port0 = 8011;
  Ipv4Address addr0 ("10.1.1.1");// p2p 1 serveur
  InetSocketAddress Add0 = InetSocketAddress (addr0, port0);
  N0->Bind (Add0);
  N0->SetRecvCallback (MakeCallback (&Recevoir_N0));

  Ptr<Socket> N1 = Socket::CreateSocket (p2pNodes1.Get (1), TypeId::LookupByName ("ns3::UdpSocketFactory"));
  uint16_t port1 = 8012;
  Ipv4Address addr1 ("10.1.1.2");// p2p 1 client 1
  InetSocketAddress Add1 = InetSocketAddress (addr1, port1);
  N1->Bind (Add1);
  N1->SetRecvCallback (MakeCallback (&Recevoir_N1));

  Ptr<Socket> N2 = Socket::CreateSocket (p2pNodes2.Get (1), TypeId::LookupByName ("ns3::UdpSocketFactory"));
  uint16_t port2 = 8022;
  Ipv4Address addr2 ("10.1.2.2");// p2p 2 client 2
  InetSocketAddress Add2 = InetSocketAddress (addr2, port2);
  N2->Bind (Add2);
  N2->SetRecvCallback (MakeCallback (&Recevoir_N2));

  Ptr<Socket> N3 = Socket::CreateSocket (p2pNodes3.Get (1), TypeId::LookupByName ("ns3::UdpSocketFactory"));
  uint16_t port3 = 8032;
  Ipv4Address addr3 ("10.1.3.2");// p2p 3 client 3
  InetSocketAddress Add3 = InetSocketAddress (addr3, port3);
  N3->Bind (Add3);
  N3->SetRecvCallback (MakeCallback (&Recevoir_N3));

  Ptr<Socket> N4 = Socket::CreateSocket (p2pNodes4.Get (1), TypeId::LookupByName ("ns3::UdpSocketFactory"));
  uint16_t port4 = 8042;
  Ipv4Address addr4 ("10.1.4.2");// p2p 4 client 4
  InetSocketAddress Add4 = InetSocketAddress (addr4, port4);
  N4->Bind (Add4);
  N4->SetRecvCallback (MakeCallback (&Recevoir_N4));

  Ptr<Socket> N5 = Socket::CreateSocket (p2pNodes5.Get (1), TypeId::LookupByName ("ns3::UdpSocketFactory"));
  uint16_t port5 = 8052;
  Ipv4Address addr5 ("10.1.5.2");// p2p 5 client 5
  InetSocketAddress Add5 = InetSocketAddress (addr5, port5);
  N5->Bind (Add5);
  N5->SetRecvCallback (MakeCallback (&Recevoir_N5));

  //valeur de confiance bonne
  Simulator::Schedule (Seconds (2),&Envoyer, N1, addr0, port0, 6);
  Simulator::Schedule (Seconds (3),&Envoyer, N2, addr0, port0, 8);

  //valeur de confiance mauvaise
  Simulator::Schedule (Seconds (4),&Envoyer, N3, addr0, port0, 1);
  Simulator::Schedule (Seconds (5),&Envoyer, N4, addr0, port0, 2);

  //valeur de confiance aleatoire
  Simulator::Schedule (Seconds (6),&Envoyer, N5, addr0, port0, 9);

  Ipv4GlobalRoutingHelper::PopulateRoutingTables ();

  Simulator::Stop (Seconds (10.0));


  AnimationInterface anim("projet.xml");  
  anim.SetConstantPosition(p2pNodes1.Get(0), 49, 25);
  anim.SetConstantPosition(p2pNodes1.Get(1), 25, 45);
  anim.SetConstantPosition(p2pNodes2.Get(1), 35, 45);
  anim.SetConstantPosition(p2pNodes3.Get(1), 49, 45);
  anim.SetConstantPosition(p2pNodes4.Get(1), 55, 45);
  anim.SetConstantPosition(p2pNodes5.Get(1), 65, 45);


  Simulator::Run ();
  Simulator::Destroy ();
  return 0;

}


void Envoyer (Ptr<Socket> sock, Ipv4Address dstaddr, uint16_t port, uint16_t i)
{
  if (i == 6){
    std::stringstream ss;
    ss << i;
    std::string message = ss.str();

    std::cout << "noeud 1 envoie la demande d'acces au donner au noeud : " << dstaddr << " avec la valeur de confiance " << i << "\n";
    Ptr<Packet> p = Create<Packet>((uint8_t *)message.c_str(), message.length()); // Envoyer la valeur de i
    sock->SendTo(p, 0, InetSocketAddress(dstaddr, port));
  }

  if (i == 8) {
    std::stringstream ss;
    ss << i;
    std::string message = ss.str();

    std::cout << "noeud 2 envoie la demande d'acces au donner au noeud : " << dstaddr << " avec la valeur de confiance " << i << "\n";
    Ptr<Packet> p = Create<Packet>((uint8_t *)message.c_str(), message.length()); // Envoyer la valeur de i
    sock->SendTo(p, 0, InetSocketAddress(dstaddr, port));
  }

  if (i == 1) {
    std::stringstream ss;
    ss << i;
    std::string message = ss.str();
 
    std::cout << "noeud 3 envoie la demande d'acces au donner au noeud : " << dstaddr << " avec la valeur de confiance " << i << "\n";
    Ptr<Packet> p = Create<Packet>((uint8_t *)message.c_str(), message.length()); // Envoyer la valeur de i
    sock->SendTo(p, 0, InetSocketAddress(dstaddr, port));
  }

  if (i == 2) {
    std::stringstream ss;
    ss << i;
    std::string message = ss.str();

    std::cout << "noeud 4 envoie la demande d'acces au donner au noeud : " << dstaddr << " avec la valeur de confiance " << i << "\n";
    Ptr<Packet> p = Create<Packet>((uint8_t *)message.c_str(), message.length()); // Envoyer la valeur de i
    sock->SendTo(p, 0, InetSocketAddress(dstaddr, port));
  }
  
  if (i == 9) {
    std::stringstream ss;
    ss << i;
    std::string message = ss.str();

    std::cout << "noeud 5 envoie la demande d'acces au donner au noeud : " << dstaddr << " avec la valeur de confiance " << i << "\n";
    Ptr<Packet> p = Create<Packet>((uint8_t *)message.c_str(), message.length()); // Envoyer la valeur de i
    sock->SendTo(p, 0, InetSocketAddress(dstaddr, port));
  }
}

void Recevoir_N0(Ptr<Socket> socket)
{
  Address from;
  Ptr<Packet> packet = socket->RecvFrom(from);
  InetSocketAddress address = InetSocketAddress::ConvertFrom(from);
  uint8_t buf[packet->GetSize()];
  packet->CopyData(buf, packet->GetSize());

  // Convertir le buffer en une chaîne de caractères pour l'affichage
  std::string receivedMessage(reinterpret_cast<char *>(buf), packet->GetSize());
  NS_LOG_INFO("noeud 0 recois " << receivedMessage << "\t Size: " << packet->GetSize() << " bytes \t from: " << address.GetIpv4());

  // Extraire la valeur de i du message reçu
  uint16_t i;
  std::istringstream(receivedMessage) >> i;
  std::string responseMessage;
  
  if (i > 5)
  {
    responseMessage = "acces autoriser";
  }
  else
  {
    responseMessage = "acces refuser ";
  }

  // Envoyer la réponse à l'adresse IP d'origine
  Ptr<Packet> p = Create<Packet>((uint8_t *)responseMessage.c_str(), responseMessage.length());
  socket->SendTo(p, 0, InetSocketAddress(address.GetIpv4(), address.GetPort()));
}


void Recevoir_N1 (Ptr<Socket> socket)
{
  Address from;
  Ptr<Packet> packet = socket->RecvFrom (from);
  InetSocketAddress address = InetSocketAddress::ConvertFrom (from);
  uint8_t buf[packet->GetSize()];
  packet->CopyData(buf,packet->GetSize());
  NS_LOG_INFO ("noeud 1 recois :" << buf << "\t Size: "<<packet->GetSize ()<< " bytes \t from: " << address.GetIpv4 ());
  std::cout << "\n";

}

void Recevoir_N2 (Ptr<Socket> socket)
{
  Address from;
  Ptr<Packet> packet = socket->RecvFrom (from);
  InetSocketAddress address = InetSocketAddress::ConvertFrom (from);
  uint8_t buf[packet->GetSize()];
  packet->CopyData(buf,packet->GetSize());
  NS_LOG_INFO ("noeud 2 recois :" << buf << "\t Size: "<<packet->GetSize ()<< " bytes \t from: " << address.GetIpv4 ());
  std::cout << "\n";

}

void Recevoir_N3 (Ptr<Socket> socket)
{
  Address from;
  Ptr<Packet> packet = socket->RecvFrom (from);
  InetSocketAddress address = InetSocketAddress::ConvertFrom (from);
  uint8_t buf[packet->GetSize()];
  packet->CopyData(buf,packet->GetSize());
  NS_LOG_INFO ("noued 3 recois :" << buf << "\t Size: "<<packet->GetSize ()<< " bytes \t from: " << address.GetIpv4 ());
  std::cout << "\n";

}

void Recevoir_N4 (Ptr<Socket> socket)
{
  Address from;
  Ptr<Packet> packet = socket->RecvFrom (from);
  InetSocketAddress address = InetSocketAddress::ConvertFrom (from);
  uint8_t buf[packet->GetSize()];
  packet->CopyData(buf,packet->GetSize());
  NS_LOG_INFO ("noeud 4 recois :" << buf << "\t Size: "<<packet->GetSize ()<< " bytes \t from: " << address.GetIpv4 ());
  std::cout << "\n";

}

void Recevoir_N5 (Ptr<Socket> socket)
{
  Address from;
  Ptr<Packet> packet = socket->RecvFrom (from);
  InetSocketAddress address = InetSocketAddress::ConvertFrom (from);
  uint8_t buf[packet->GetSize()];
  packet->CopyData(buf,packet->GetSize());
  NS_LOG_INFO ("noeud 5 recois :" << buf << "\t Size: "<<packet->GetSize ()<< " bytes \t from: " << address.GetIpv4 ());
  std::cout << "\n";

}
