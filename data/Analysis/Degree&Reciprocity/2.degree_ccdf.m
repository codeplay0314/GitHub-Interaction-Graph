close;
figure(1);
[data1, data2] = textread('degree.txt', '%n%n', 6012074, 'delimiter', ',');
data = [data1 data2]';
data = sort(data, 2);
len = length(data(1, :));
maxdata = max(sum(data, 2), [], 'all');

exp1_x_cls1 = [];
exp1_y_cls1 = [];
exp1_x_cls2 = [];
exp1_y_cls2 = [];
exp1_x_cls3 = [];
exp1_y_cls3 = [];

for i = 1: len
    if i == len || data(1, i) ~= data(1, i + 1)
        exp1_x_cls1 = [exp1_x_cls1, data(1, i)];
        exp1_y_cls1 = [exp1_y_cls1, i / len];
    end
end
for i = 1: len
    if i == len || data(2, i) ~= data(2, i + 1)
        exp1_x_cls2 = [exp1_x_cls2, data(2, i)];
        exp1_y_cls2 = [exp1_y_cls2, i / len];
    end
end
data3 = zeros(1, len);
for i = 1: len
    data3(1, i) = data(1, i) + data(2, i);
end
for i = 1: len
    if i == len || data3(1, i) ~= data3(1, i + 1)
        exp1_x_cls3 = [exp1_x_cls3, data3(1, i)];
        exp1_y_cls3 = [exp1_y_cls3, i / len];
    end
end

exp1_y_cls1 = 100 - exp1_y_cls1 * 100;
exp1_y_cls2 = 100 - exp1_y_cls2 * 100;
exp1_y_cls3 = 100 - exp1_y_cls3 * 100;

p = semilogx(exp1_x_cls1, exp1_y_cls1, exp1_x_cls2, exp1_y_cls2)
xlabel('Degree')
ylabel('Percentage(%)')
set(gca, 'FontSize', 16)
axis([0,1000,0,50])
l1 = p(1)
l1.LineWidth = 1
l1.LineStyle = '--'
l2 = p(2)
l2.LineWidth = 1
hold on
lg = legend('Incoming Degree', 'Outgoing Degree', 'FontSize', 10)
% set(gca, 'color', [0.8941    0.8941    0.8941], 'LineWidth', 1)
set(gca, 'LineWidth', 1)
set(gca,'GridColor',[1 1 1], 'GridAlpha', 1)
% set(gca, 'xTick',[0:2:10],'yTick',[0:0.2:1])
% box off;                                                                                                                    

figure(2);
degree = [256190 763941 763941; 208760 256191 71237; 151584 208760 55467; 116660 151584 25090; 104728 116660 15915; 100941 104728 13273; 95728 100941 13264; 80319 95728 12554; 74307 80319 9777; 70579 74307 9403
];
degree(2, :)
degree = [degree(:, 2) degree(:, 1) degree(:, 3)];

B1 = bar((1:10), degree, 'BarWidth', 1, 'LineStyle', 'none')
% b1 = B1(1)
b1.FaceColor = [95 69 49]/255
% b2 = B1(2)
b2.FaceColor = [236,186,135]/255
ylim([1000,770000])
ylabel('Number')
grid on
lg = legend('Total Degree', 'Incoming Degree', 'Outgoing Degree', 'FontSize', 12)
set(gca, 'xticklabel', {'1st', '2nd', '3rd', '4th', '5th', '6th', '7th', '8th', '9th', '10th'})
set(gca, 'GridLineStyle',':')