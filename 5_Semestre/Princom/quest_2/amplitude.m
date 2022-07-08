fn=-10:10;
Dn=2*cos(pi*fn)./fn.^2;
Dn(11)=(pi^2)/3;

stem(fn,abs(Dn),'filled','MarkerFaceColor','auto','LineWidth',2);
title('Espectro de Amplitude','FontSize',18);
xlabel('nw_0 (Hz)');
ylabel('| D_n |','Rotation',0);