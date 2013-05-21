(* ::Package:: *)

ClearAll["Global`*"]
SetOptions[{Plot,ParametricPlot, ListLinePlot, ListPlot, LogLinearPlot},BaseStyle->{FontFamily->"Latin Modern Roman", FontSize->11}];
imgSize = 200;
imagePadding = {{30, 10}, {20, 4}};

bqF = 15;
bq = bqF*2Pi;

s = I 2Pi f ;
tt = bq/(bq+s);
tf = ButterworthFilterModel[{1, bq}, ss];
BodePlot[tf];

p0 = LogLinearPlot[Abs[tt], {f, 0.5, 100}, ImageSize->imgSize, ImagePadding->imagePadding, FrameTicks->{{{0, 1}, None}, {{0, 1, 10, 100}, None}}, Frame->True, PlotRange->{0, 1.01}]
p1 = LogLinearPlot[Arg[tt], {f, 0.5, 100}, ImageSize->imgSize, ImagePadding->imagePadding, Frame->True, FrameTicks->{{{0, -Pi/4, -Pi/2}, None}, {{0, 1, 10, 100}, None}}, PlotRange->{0, -Pi/2}]


Export["~/kandidat/Slutrapport/img/filter/butter_abs.pdf", p0]
Export["~/kandidat/Slutrapport/img/filter/butter_phase.pdf", p1]



