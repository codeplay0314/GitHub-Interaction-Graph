close;
figure(1);
[data1, data2, data3] = textread('degree.txt', '%d%d%d', 6012074, 'delimiter', ' ');

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
x21 = zeros(1, 10000);
y21 = zeros(1, 10000);
x22 = zeros(1, 10000);
y22 = zeros(1, 10000);
x31 = zeros(1, 10000);
y31 = zeros(1, 10000);
x32 = zeros(1, 10000);
y32 = zeros(1, 10000);

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

y11 = 100 - y11 * 100;
y12 = 100 - y12 * 100;
y21 = 100 - y21 * 100;
y22 = 100 - y22 * 100;
y31 = 100 - y31 * 100;
y32 = 100 - y32 * 100;

p = semilogx(x11, y11, x12, y12, x31, y31, x32, y32);
hold on
set(gca, 'FontSize', 16);
xlabel('Degree');
ylabel('Percentage(%)');
axis([0, 100000, 0, 100]);
l1 = p(1);
l2 = p(2);
l3 = p(3);
l4 = p(4);
% l5 = p(5);
% l6 = p(6);
l1.LineWidth = 1;
l2.LineWidth = 1;
l3.LineWidth = 1;
l4.LineWidth = 1;
% l5.LineWidth = 1;
% l6.LineWidth = 1;
% l6.Color = l3.Color;
% l5.Color = l3.Color;
l4.Color = l2.Color;
l3.Color = l2.Color;
l2.Color = l1.Color;
%l1.Color = [0.50, 0.50, 0.50];
%l2.Color = [0.50, 0.50, 0.50];
%l3.Color = [1.00, 0.38, 0.01];
%l4.Color = [1.00, 0.38, 0.01];
%l5.Color = [0.25, 0.88, 0.82];
%l6.Color = [0.25, 0.88, 0.82];
l1.LineStyle = '-.';
l2.LineStyle = ':';
l3.LineStyle = '--';
% l6.LineStyle = '--';
hold on
lg = legend('Incoming Degree of Ordinary Users', 'Outgoing Degree of Ordinary Users', 'Incoming Degree of SH Spanners', 'Outgoing Degree of SH Spanners', 'FontSize', 14);
% lg = legend('Incoming Degree of Ordinary Users', 'Outgoing Degree of Ordinary Users', 'Total Degree of Ordinary Users', 'Incoming Degree of SH Spanners (HIS)', 'Outgoing Degree of SH Spanners (HIS)', 'Total Degree of SH Spanners (HIS)', 'FontSize', 8);
% set(gca, 'color', [0.8941    0.8941    0.8941], 'LineWidth', 1)
set(gca,'GridColor',[1 1 1], 'GridAlpha', 1)
% set(gca, 'xTick',[0:2:10],'yTick',[0:0.2:1])                                                                                                                