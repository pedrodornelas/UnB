fn=-10:10;
Dn=[0 pi 0 pi 0 pi 0 pi 0 pi 0 -pi 0 -pi 0 -pi 0 -pi 0 -pi 0]

stem(fn,Dn,'filled','MarkerFaceColor','auto','LineWidth',2);
title('Espectro de Fase','FontSize',18);
xlabel('nw_0 (Hz)');
ylabel('\angle D_n','Rotation',0);