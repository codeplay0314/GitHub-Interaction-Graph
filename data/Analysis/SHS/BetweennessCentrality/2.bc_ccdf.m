close;
figure(1);
ord = textread('bc_ord_his.txt', '%f', 6002074)';
con = textread('bc_shs_con.txt', '%f', 10000)';
his = textread('bc_shs_his.txt', '%f', 10000)';
maxdata = max(max(max(ord, [], 'all'), max(con, [], 'all')), max(his, [], 'all'));

x1 = zeros(1, 6002074);
y1 = zeros(1, 6002074);
x2 = zeros(1, 10000);
y2 = zeros(1, 10000);
x3 = zeros(1, 10000);
y3 = zeros(1, 10000);

ord = sort(ord, 2);
con = sort(con, 2);
his = sort(his, 2);

cnt1 = 6002074;
cnt2 = 10000;
cnt3 = 10000;

y = 0;
for i = 1: cnt1
    if i == cnt1 || ord(1, i) ~= ord(1, i + 1)
        y = y + 1;
        x1(1, y) = ord(1, i);
        y1(1, y) = i / cnt1;
    end
end
x1 = x1(1, 1: y);
y1 = y1(1, 1: y);
y = 0;
for i = 1: cnt2
    if i == cnt2 || con(1, i) ~= con(1, i + 1)
        y = y + 1;
        x2(1, y) = con(1, i);
        y2(1, y) = i / cnt2;
    end
end
x2 = x2(1, 1: y);
y2 = y2(1, 1: y);
y = 0;
for i = 1: cnt3
    if i == cnt3 || his(1, i) ~= his(1, i + 1)
        y = y + 1;
        x3(1, y) = his(1, i);
        y3(1, y) = i / cnt3;
    end
end
x3 = x3(1, 1: y);
y3 = y3(1, 1: y);

y1 = 100 - y1 * 100;
y2 = 100 - y2 * 100;
y3 = 100 - y3 * 100;

p = semilogx(x1, y1, x3, y3);
xlabel('Betweenness Centrality (K = 10000)');
ylabel('Percentage(%)');
set(gca, 'FontSize', 16);
axis([0, maxdata, 0, 100]);
l1 = p(1);
l1.LineStyle = '--';
l1.LineWidth = 1;
l2 = p(2);
l2.LineWidth = 1;
% l3 = p(3);
% l3.LineWidth = 1;
hold on;
lg = legend('Ordinary Users','SH Spanners', 'FontSize', 14);
% set(gca, 'color', [0.8941    0.8941    0.8941], 'LineWidth', 1);
set(gca,'GridColor',[1 1 1], 'GridAlpha', 1);
% set(gca, 'xTick',[0:2:10],'yTick',[0:0.2:1])  