#include <iostream>

  using namespace std;
  int main () {

  	double RI, RF, R1, R2, R3, R4, R5, V1, V2, V3, Vin, Vo, Vc, Vs, i1, i2, i3, i4, i5, iR, Is, Il, a, L, t, batata, SUM, SeqR1R2, C8, Coiso, Ilinf, tauq5,cap5;
  	
  	cout << "WELCOME TO CHUTOMETRO - All rights deserved" << endl << endl;
  	
	cout << "Questao 1. Digite os valores solicitados:" << endl;
  	
	cout << "Digite o valor para R2: ";
	cin >> R2;
	cout << endl;
	
	cout << "Digite o valor para Is: ";
	cin >> Is;
	cout << endl;
	
	Vo = -Is*R2;
	cout << "Vo = " << Vo << endl;
	cout << "i3 = " << Is << endl << endl;
	
	
//------------------------------------------------------------------------------------------------------------------	
	
	
	cout << "Questao 2. Digite os valores solicitados:" << endl;
  	
	cout << "Digite o valor para V1: ";
	cin >> V1;
	cout << endl;
	
	cout << "Digite o valor para V2: ";
	cin >> V2;
	cout << endl;
	
  	cout << "Digite o valor para R1: ";
	cin >> R1;
	cout << endl;
	
	cout << "Digite o valor para R2: ";
	cin >> R2;
	cout << endl;
	
	cout << "Digite o valor para R3: ";
	cin >> R3;
	cout << endl;
	
	Vo = V1*(1+(R3/R2)+(R3/R1))-V2*(R3/R1);
	iR = (V1-Vo)/R3;
	cout << "Vo = " << Vo << endl;
	cout << "iR3 = " << iR << endl << endl;
		

//------------------------------------------------------------------------------------------------------------------	
	
	cout << "Questao 3. Digite os valores solicitados:" << endl;
  	
	cout << "Digite o valor para V1: ";
	cin >> V1;
	cout << endl;
	
	cout << "Digite o valor para V2: ";
	cin >> V2;
	cout << endl;
	
  	cout << "Digite o valor para R1: ";
	cin >> R1;
	cout << endl;
	
	cout << "Digite o valor para R2: ";
	cin >> R2;
	cout << endl;
		
	Vo = (1+(R2/R1))*V1-(R2/R1)*V2;

	cout << "Vo = " << Vo << endl << endl;
			

//------------------------------------------------------------------------------------------------------------------	
	
	cout << "Questao 4. Digite os valores solicitados:" << endl;
  	
	cout << "Digite o valor para Vin: ";
	cin >> Vin;
	cout << endl;
	
	cout << "Digite o valor para R1: ";
	cin >> R1;
	cout << endl;
	
  	cout << "Digite o valor para R2: ";
	cin >> R2;
	cout << endl;
	
	cout << "Digite o valor para RI: ";
	cin >> RI;
	cout << endl;
	
	cout << "Digite o valor para RF: ";
	cin >> RF;
	cout << endl;
		
	Vo = (((RI+RF)/RI)*(R2/(R1+R2)))*Vin;

	cout << "Vo = " << Vo << "(arredonde)" << endl << endl;

	
//------------------------------------------------------------------------------------------------------------------	
	
	cout << "Questao 5. Digite os valores solicitados:" << endl;
  	
	
	cout << "Digite o valor para R1: ";
	cin >> R1;
	cout << endl;
	
  	cout << "Digite o valor para R2: ";
	cin >> R2;
	cout << endl;
	
	cout << "Digite o valor para R3: ";
	cin >> R3;
	cout << endl;
	
	cout << "Digite o valor para R4: ";
	cin >> R4;
	cout << endl;
	
	cout << "Digite o valor para o Capacitor: ";
	cin >> cap5;
	cout << endl;
	
	cout << "Digite o valor para Vs: ";
	cin >> Vs;
	cout << endl;
		
	Vo = ((R3+R4)/(R1+R2+R3+R4))*Vs;
	tauq5 = cap5*(R2*(R3+R4)/(R2+R3+R4));

	cout << "Vc(0-) = " << Vo << endl << endl;
	cout << "constante de tempo = " << tauq5 << endl << endl;

	
//------------------------------------------------------------------------------------------------------------------

	
	cout << "Questao 6 (Melhor usar o arquivo Python) Digite os valores solicitados:" << endl;
  		
	cout << "Digite o valor para R3: ";
	cin >> R3;
	cout << endl;
	
	cout << "Digite o valor para R4: ";
	cin >> R4;
	cout << endl;
	
	cout << "Digite o valor para L: ";
	cin >> L;
	cout << endl;
	
	t = (R3*R4)/L;
	
	cout << "t = " << t << endl << endl;	
	cout << "Questao 7 - Usar algoritmo em Python" << endl << endl;	
//------------------------------------------------------------------------------------------------------------------	
	
	cout << "Questao 8. Digite os valores solicitados:" << endl;
  	
	
	cout << "Digite o valor para Vs: ";
	cin >> Vs;
	cout << endl;
	
	cout << "Digite o valor para Is: ";
	cin >> Is;
	cout << endl;
	
	cout << "Digite o valor para R1: ";
	cin >> R1;
	cout << endl;
	
  	cout << "Digite o valor para R2: ";
	cin >> R2;
	cout << endl;
	
	cout << "Digite o valor para L: ";
	cin >> L;
	cout << endl;
	
	cout << "Digite o valor para a (alfa): ";
	cin >> a;
	cout << endl;
			
	Il = ((1+a)*Vs)/R2;
	SUM = Is * R1;
	SeqR1R2 = R2+R1;
	Coiso = (a*R2)/(1+a);
	C8 = SeqR1R2 - Coiso;

	Ilinf = SUM/C8;		

	cout << "A corrente no indutor em t=0 e " << Il << endl;
	cout << "A corrente no indutor apos ele se carregar completamente e " << Ilinf << endl << endl;	
	
	cout << "Questao 9 - Sempre chutar o maior valor. " << endl <<	endl << "Questao 10 - Usar o arquivo Python." << endl;
	cin >> batata;	
		    	
	return 0;
  }

