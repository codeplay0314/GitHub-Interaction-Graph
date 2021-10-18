load('comm.mat')
x = 1:1:73913;
p = plot(x, comm);
xlabel('Communities')
ylabel('Percentage')
set(gca, 'FontSize', 20)
axis([0,100,0,1])
l1 = p(1);
l1.LineWidth = 3;
l1.LineStyle = '-';
hold on
set(gca, 'color', [0.8941    0.8941    0.8941], 'LineWidth', 1)
grid on
set(gca,'GridColor',[1 1 1], 'GridAlpha', 1)
set(gca, 'xTick',[0:20:100],'yTick',[0:0.2:1])
box off