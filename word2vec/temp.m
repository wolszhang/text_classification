load input1train
load input2train
load input1test
load input2test
 
[x,~] = size(input2train);
[y,~] = size(input1train);
[a,~] = size(input2test);
[b,~] = size(input1test);
S = 3;
C = 1;
e = 0.1;
B = 1;

parameters = sprintf('-s 3 -c 1 -e 0.1 -B 1', S, C, e, B);
input = [input2train;input1train];
output = [ones(x,1);zeros(y,1)];
test = [input2test;input1test];
mylabel = [ones(a,1);zeros(b,1)];
model = train(output,sparse(input),parameters);
[label,accuracy,prob] = predict(mylabel,sparse(test),model);

B = 2;
parameters = sprintf('-s %d -c %1.5f -e %1.5f -B %1.3f', S, C, e, B);
input = [input2train;input1train];
output = [ones(x,1);zeros(y,1)];
test = [input2test;input1test];
mylabel = [ones(a,1);zeros(b,1)];
model = train(output,sparse(input),parameters);
[label,accuracy,prob] = predict(mylabel,sparse(test),model);

B = 3;
parameters = sprintf('-s %d -c %1.5f -e %1.5f -B %1.3f', S, C, e, B);
input = [input2train;input1train];
output = [ones(x,1);zeros(y,1)];
test = [input2test;input1test];
mylabel = [ones(a,1);zeros(b,1)];
model = train(output,sparse(input),parameters);
[label,accuracy,prob] = predict(mylabel,sparse(test),model);



