f=800000000;
c=300000000;
lambda=c/f;

d=1:1:400000;

Gt=lambda^2/(4*pi);
Gr=Gt;

ht=10;
hr=ht;

LEP=-10*log10(Gt)-10*log10(Gr)-20*log10(lambda)+20.*log10(d)+21.98;
LPT=-10*log10(Gt)-10*log10(Gr)-20*log10(ht)-20*log10(hr)+40.*log10(d);

semilogx(d,LEP , d,LPT);
//plot(d,LEP , d,LPT);
title("Perda no Espaço-Livre x Plano-Terra", "FontSize", 18);
xlabel("Distância(m)");
ylabel("Perda(dB)");
legend("Espaço-Livre","Plano-Terra");