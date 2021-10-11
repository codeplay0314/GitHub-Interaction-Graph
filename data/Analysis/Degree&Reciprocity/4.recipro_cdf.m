close;
data = textread('reciprocity.txt', '%n', 6012074);
data = data';
data = sort(data, 2);
len = length(data);
maxdata = max(data, [], 'all');

exp1_x_cls1 = [];
exp1_y_cls1 = [];

for i = 1: len
    if i == len || data(1, i) ~= data(1, i + 1)
        exp1_x_cls1 = [exp1_x_cls1, data(1, i)];
        exp1_y_cls1 = [exp1_y_cls1, i / len];
    end
end

p = plot(exp1_x_cls1, exp1_y_cls1)
xlabel('Reciprocity')
ylabel('Percentage(%)')
set(gca, 'FontSize', 10)
axis([0,maxdata,0.975,1])
l1 = p(1)
l1.LineWidth = 1
hold on
set(gca, 'color', [0.8941    0.8941    0.8941], 'LineWidth', 1)
grid on
set(gca,'GridColor',[1 1 1], 'GridAlpha', 1)
% set(gca, 'xTick',[0:2:10],'yTick',[0:0.2:1])
box off