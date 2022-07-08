clear all

T = input("Digite T:");
potencia=(0.97*2)/(T*3);
passo=0.001;
f=passo;

# O primeiro valor já setado
integral=1*passo;

while(integral < potencia)
  #função a ser integrada
  s=((sin((pi*f*T)/2))/((pi*f*T)/2))^4;
  integral = integral + s*passo;
  f=f+passo;
endwhile

printf("A largura de banda para T=%d é de f=%d Hz .\n",T,f);