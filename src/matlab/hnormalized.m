function y = hnormalized(x)
    y = x/x(end);
    y = y(1:end-1);
