close;
figure(1);
[data1, data2, data3] = textread('num_connected_community.txt', '%d%d%d', 6012074, 'delimiter', ' ');

isCON = zeros(1, 6012074);
[SHS, vac] = textread('../../Constraint.txt', '%d %f', 10000);
for i = 1: 10000
    isCON(1, SHS(i, 1) + 1) = 1;
end

isHIS = zeros(1, 6012074);
[SHS, vac] = textread('../../HIS.txt', '%d %f', 10000);
for i = 1: 10000
    isHIS(1, SHS(i, 1) + 1) = 1;
end

x11 = zeros(1, 6002074);
y11 = zeros(1, 6002074);
x12 = zeros(1, 6002074);
y12 = zeros(1, 6002074);
x13 = zeros(1, 6002074);
y13 = zeros(1, 6002074);
x21 = zeros(1, 10000);
y21 = zeros(1, 10000);
x22 = zeros(1, 10000);
y22 = zeros(1, 10000);
x23 = zeros(1, 10000);
y23 = zeros(1, 10000);
x31 = zeros(1, 10000);
y31 = zeros(1, 10000);
x32 = zeros(1, 10000);
y32 = zeros(1, 10000);
x33 = zeros(1, 10000);
y33 = zeros(1, 10000);


maxdata = 0;
ord = zeros(1, 6012074);
con = zeros(1, 10000);
his = zeros(1, 10000);

cnt1 = 0;
cnt2 = 0;
cnt3 = 0;
for i = 1: 6012074
    maxdata = max(maxdata, data1(i, 1));
    cnt1 = cnt1 + 1;
    ord(1, cnt1) = data1(i, 1);
    if isCON(1, i) == 1
        cnt2 = cnt2 + 1;
        con(1, cnt2) = data1(i, 1);
    end
    if isHIS(1, i) == 1
        cnt3 = cnt3 + 1;
        his(1, cnt3) = data1(i, 1);
    end
end

ord = sort(ord, 2);
con = sort(con, 2);
his = sort(his, 2);

y = 0;
for i = 1: cnt1
    if i == cnt1 || ord(1, i) ~= ord(1, i + 1)
        y = y + 1;
        x11(1, y) = ord(1, i);
        y11(1, y) = i / cnt1;
    end
end
x11 = x11(1, 1: y);
y11 = y11(1, 1: y);
y = 0;
for i = 1: cnt2
    if i == cnt2 || con(1, i) ~= con(1, i + 1)
        y = y + 1;
        x21(1, y) = con(1, i);
        y21(1, y) = i / cnt2;
    end
end
x21 = x21(1, 1: y);
y21 = y21(1, 1: y);
y = 0;
for i = 1: cnt3
    if i == cnt3 || his(1, i) ~= his(1, i + 1)
        y = y + 1;
        x31(1, y) = his(1, i);
        y31(1, y) = i / cnt3;
    end
end
x31 = x31(1, 1: y);
y31 = y31(1, 1: y);

cnt1 = 0;
cnt2 = 0;
cnt3 = 0;
for i = 1: 6012074
    maxdata = max(maxdata, data2(i, 1));
    cnt1 = cnt1 + 1;
    ord(1, cnt1) = data2(i, 1);
    if isCON(1, i) == 1
        cnt2 = cnt2 + 1;
        con(1, cnt2) = data2(i, 1);
    end
    if isHIS(1, i) == 1
        cnt3 = cnt3 + 1;
        his(1, cnt3) = data2(i, 1);
    end
end

ord = sort(ord, 2);
con = sort(con, 2);
his = sort(his, 2);

y = 0;
for i = 1: cnt1
    if i == cnt1 || ord(1, i) ~= ord(1, i + 1)
        y = y + 1;
        x12(1, y) = ord(1, i);
        y12(1, y) = i / cnt1;
    end
end
x12 = x12(1, 1: y);
y12 = y12(1, 1: y);
y = 0;
for i = 1: cnt2
    if i == cnt2 || con(1, i) ~= con(1, i + 1)
        y = y + 1;
        x22(1, y) = con(1, i);
        y22(1, y) = i / cnt2;
    end
end
x22 = x22(1, 1: y);
y22 = y22(1, 1: y);
y = 0;
for i = 1: cnt3
    if i == cnt3 || his(1, i) ~= his(1, i + 1)
        y = y + 1;
        x32(1, y) = his(1, i);
        y32(1, y) = i / cnt3;
    end
end
x32 = x32(1, 1: y);
y32 = y32(1, 1: y);

cnt1 = 0;
cnt2 = 0;
cnt3 = 0;
for i = 1: 6012074
    maxdata = max(maxdata, data3(i, 1));
    cnt1 = cnt1 + 1;
    ord(1, cnt1) = data3(i, 1);
    if isCON(1, i) == 1
        cnt2 = cnt2 + 1;
        con(1, cnt2) = data3(i, 1);
    end
    if isHIS(1, i) == 1
        cnt3 = cnt3 + 1;
        his(1, cnt3) = data3(i, 1);
    end
end

ord = sort(ord, 2);
con = sort(con, 2);
his = sort(his, 2);

y = 0;
for i = 1: cnt1
    if i == cnt1 || ord(1, i) ~= ord(1, i + 1)
        y = y + 1;
        x13(1, y) = ord(1, i);
        y13(1, y) = i / cnt1;
    end
end
x13 = x13(1, 1: y);
y13 = y13(1, 1: y);
y = 0;
for i = 1: cnt2
    if i == cnt2 || con(1, i) ~= con(1, i + 1)
        y = y + 1;
        x23(1, y) = con(1, i);
        y23(1, y) = i / cnt2;
    end
end
x23 = x23(1, 1: y);
y23 = y23(1, 1: y);
y = 0;
for i = 1: cnt3
    if i == cnt3 || his(1, i) ~= his(1, i + 1)
        y = y + 1;
        x33(1, y) = his(1, i);
        y33(1, y) = i / cnt3;
    end
end
x33 = x33(1, 1: y);
y33 = y33(1, 1: y);

y11 = 100 - y11 * 100;
y12 = 100 - y12 * 100;
y13 = 100 - y13 * 100;
y21 = 100 - y21 * 100;
y22 = 100 - y22 * 100;
y23 = 100 - y23 * 100;
y31 = 100 - y31 * 100;
y32 = 100 - y32 * 100;
y33 = 100 - y33 * 100;

p = semilogx(x13, y13, '--', x33, y33, '-');
% p = semilogx(x11, y11, '-+', x12, y12, '--+', x13, y13, ':+', x31, y31, '-', x32, y32, '--', x33, y33, ':');
hold on;
xlabel('Number of Connected Communities');
ylabel('Percentage(%)');
set(gca, 'FontSize', 16);
axis([0, 100, 0, 100]);
l1 = p(1);
l2 = p(2);
% l3 = p(3);
% l4 = p(4);
% l5 = p(5);
% l6 = p(6);
% l7 = p(7);
% l8 = p(8);
% l9 = p(9);
% l9.Color = l3.Color;
% l8.Color = l3.Color;
% l7.Color = l3.Color;
% l6.Color = l2.Color;
% l5.Color = l2.Color;
% l4.Color = l2.Color;
% l3.Color = l1.Color;
% l2.Color = l1.Color;
l1.LineWidth = 1;
l2.LineWidth = 1;
% l3.LineWidth = 1;
% l4.LineWidth = 1;
% l5.LineWidth = 1;
% l6.LineWidth = 1;
% l7.LineWidth = 1;
% l8.LineWidth = 1;
% l9.LineWidth = 1;
% l1.LineStyle = '-';
% l2.LineStyle = '--';
% l3.LineStyle = '-.';
% l7.LineStyle = '--';
% l4.LineStyle = '-';
% l5.LineStyle = '--';
% l6.LineStyle = '-.';
% l8.LineStyle = ':';
hold on
lg = legend('Ordinary Users', 'SH Spanners', 'FontSize', 14);% 
% lg = legend('Outgoing-connected Communities of Ordinary Users', 'Incoming-connected Communities of Ordinary Users', 'Bilaterally Connected Communities of Ordinary Users', 'Outgoing-connected Communities of SH Spanners', 'Incoming-connected Communities of SH Spanners', 'Bilaterally Connected Communities of SH Spanners', 'FontSize', 10);
% lg = legend('Outgoing Connected Communities of Ordinary User', 'Incoming Connected Communities of Ordinary User', 'Bilaterally Connected Communities of Ordinary User', 'Outgoing Connected Communities of SH Spanner (HIS)', 'Incoming Connected Communities of SH Spanner (HIS)', 'Bilaterally Connected Communities of SH Spanner (HIS)', 'FontSize', 8);
% legend('Location','best');
% set(gca, 'color', [0.8941    0.8941    0.8941], 'LineWidth', 1)
set(gca,'GridColor',[1 1 1], 'GridAlpha', 1);
% set(gca, 'xTick',[0:2:10],'yTick',[0:0.2:1])                                                                                