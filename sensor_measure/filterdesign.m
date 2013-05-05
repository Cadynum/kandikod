(* ::Package:: *)

ClearAll["Global`*"]
SetOptions[{Plot,ParametricPlot, ListLinePlot, ListPlot},BaseStyle->{FontFamily->"Latin Modern Roman"}];

data = 1023-Import["~/kandikod/m\[ADoubleDot]tdata/samples", "List"];
sr = 100;
(*ListPlot[
2*Abs[Fourier[data]]/Length[data]
, DataRange\[Rule]{0,  sr}
, PlotRange\[Rule]{{0, 50}, {0, 1}}
, ImageSize\[Rule]418
, Joined\[Rule]True
,AxesLabel\[Rule]{"Hz", "|Y(f)|"}
, Filling\[Rule]Axis
]*)
ButterworthFilterModel[{1, 101}, s]
ToDiscreteTimeModel[%, 1/srr, z]
% //InputForm

Manipulate[
sys =ToDiscreteTimeModel[filtermodel[{1, bq*2 Pi}], 1/sr, z] //N;
resp = Re[OutputResponse[sys, data]];
ListLinePlot[{If[on, data], If[onbw, First[resp]]}
, AxesOrigin->{0,0}
, PlotRange->{{7, 10},{0, 1024}}
,DataRange->{0, Length[data]/sr}]
ListLinePlot[Re[OutputResponse[sys, Array[UnitStep,  sr]]], AxesOrigin->{0,0}]

, {{bq, 30, "Brytfrekvens"}, 3, 50, 1}
,{{on,True,"Visa orginal"},{True,False}}
,{{onbw,True,"Visa Filter"},{True,False}}
,{{filtermodel, ButterworthFilterModel, "Modell"}, {ButterworthFilterModel, BesselFilterModel, EllipticFilterModel}}
]
(*ListLinePlot[resp, AxesOrigin\[Rule]{0,0}]
ListLinePlot[data, AxesOrigin\[Rule]{0,0}]
ListLinePlot[Re[OutputResponse[sys, Array[UnitStep,  sr]]], AxesOrigin\[Rule]{0,0}]*)
