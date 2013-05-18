(* ::Package:: *)

ClearAll["Global`*"]
SetOptions[{Plot,ParametricPlot, ListLinePlot, ListPlot},BaseStyle->{FontFamily->"Latin Modern Roman", FontSize->11}];

data = (1023-Import["~/kandikod/m\[ADoubleDot]tdata/samples", "List"])*3.3/1024;
(*ListPlot[
2*Abs[Fourier[data]]/Length[data]
, DataRange\[Rule]{0,  sr}
, PlotRange\[Rule]{{0, 50}, {0, 1}}
, ImageSize\[Rule]418
, Joined\[Rule]True
,AxesLabel\[Rule]{"Hz", "|Y(f)|"}
, Filling\[Rule]Axis
]*)
bq = 15;
srr = 100;
ButterworthFilterModel[{1, 101}, s]
ToDiscreteTimeModel[%, 1/srr, z]

sys =ToDiscreteTimeModel[ButterworthFilterModel[{1, bq*2 Pi}], 1/srr, z] //N;
resp = RecurrenceFilter[sys, data];
p0 = ListLinePlot[{data, resp+0.05}
	(*, AxesOrigin->{0,0}*)
	, PlotRange->{{8.2, 9.2},{400*3.3/1024, 700*3.3/1024}}
	, DataRange-> {0, Length[data]/srr}
	, ImageSize -> 418
	, PlotLegends->{Style["Insignal", FontFamily->"Latin Modern Roman"], Style["Filtrerad", FontFamily->"Latin Modern Roman"]}
	, AxesLabel -> {"Tid (s)", "Sp\[ADoubleDot]nning (V)"}
(*	, Axes \[Rule] {True, False}*)
(*	, Ticks \[Rule] {Automatic, {{400, "39%"}, {700, "68%"}}}*)
]
Export["~/kandidat/Slutrapport/img/filter/tryck_dubbel.pdf", p0];
(*ListLinePlot[resp, AxesOrigin\[Rule]{0,0}]
ListLinePlot[data, AxesOrigin\[Rule]{0,0}]
ListLinePlot[Re[OutputResponse[sys, Array[UnitStep,  sr]]], AxesOrigin\[Rule]{0,0}]*)






