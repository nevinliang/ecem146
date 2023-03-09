a = zeros(n,1);
poK = @(xtest, xi) (1 + xtest' * xi)^2;

for it = 1:1000
    for test = 1:n
        p = 0;
        for i = 1:n
            p = p + a(i) * y(i) * poK(x(:,test), x(:,i));
        end
        if y(test) * p <= 0
            a(test) = a(test) + 1;
        end
    end
end

xrange = 0:0.1:4;
yrange = 0:0.1:4;
dim = length(xrange);
[x1, x2] = meshgrid(xrange, yrange);
Z = zeros(dim);
for r = 1:dim
    for c = 1:dim
        p = 0;
        for i = 1:n
            p = p + a(i) * y(i) * poK([1; x1(r,c); x2(r,c)], x(:,i));
        end
        Z(r,c) = p;
    end
end
contour(x1, x2, Z, 'LevelList', 0);

miss = 0;
for t = 1:n
    p = 0;
    for i = 1:n
        p = p + a(i) * y(i) * poK(x(:,t), x(:,i));
    end
    if (p * y(t) <= 0)
        miss = miss + 1;    
    end
end
acc = 1 - miss/n;
fprintf("polynomial kernel accuracy: %f", acc);
