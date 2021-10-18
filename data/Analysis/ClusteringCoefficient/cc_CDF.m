load('cc_x.mat')
load('cc_y.mat')
cc_y = double(cc_y)/1510452;
p = plot(cc_x,cc_y);
xlabel('Clustering Coefficient')
ylabel('Percentage')
set(gca, 'FontSize', 20)
axis([0,0.1,0,1])
l1 = p(1);
l1.LineWidth = 3;
l1.LineStyle = '-';
hold on
set(gca, 'color', [0.8941    0.8941    0.8941], 'LineWidth', 1)
grid on
set(gca,'GridColor',[1 1 1], 'GridAlpha', 1)
set(gca, 'xTick',[0:0.02:0.1],'yTick',[0:0.2:1])
box off