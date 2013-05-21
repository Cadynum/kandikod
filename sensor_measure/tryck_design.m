(* ::Package:: *)

ClearAll["Global`*"]
SetOptions[{Plot,ParametricPlot, ListLinePlot, ListPlot},BaseStyle->{FontFamily->"Latin Modern Roman", FontSize->11}];

data = (1023-Import["~/kandikod/m\[ADoubleDot]tdata/samples", "List"])*3.3/1024;

bq = 15;
srr = 100;
ButterworthFilterModel[{1, 101}, s];
ToDiscreteTimeModel[%, 1/srr, z];

dft = ListPlot[
	2*Abs[Fourier[data]]/Length[data]
	, DataRange->{0,  srr}
	, PlotRange->{{0, 50}, {0, 0.01}}
	, ImageSize->350
	, Joined->True
	, AxesLabel->{"Hz", "|Y(f)|"}
	, Filling->Axis
]

sys =ToDiscreteTimeModel[ButterworthFilterModel[{1, bq*2 Pi}], 1/srr, z] //N;
resp = RecurrenceFilter[sys, data];
p0 = ListLinePlot[{ArrayPad[data, {10, 0}], resp}
	(*, AxesOrigin->{0,0}*)
	, PlotRange->{{8.2, 9.2},{400*3.3/1024, 700*3.3/1024}}
	, DataRange-> {0, Length[data]/srr}
	, ImageSize -> 418
	, PlotLegends->{Style["Insignal", FontFamily->"Latin Modern Roman"], Style["Filtrerad", FontFamily->"Latin Modern Roman"]}
	, AxesLabel -> {"Tid (s)", "Sp\[ADoubleDot]nning (V)"}
(*	, Axes \[Rule] {True, False}*)
(*	, Ticks \[Rule] {Automatic, {{400, "39%"}, {700, "68%"}}}*)
]
(*Export["~/kandidat/Slutrapport/img/filter/flex_fourier.pdf", dft]*)
(*Export["~/kandidat/Slutrapport/img/filter/tryck_dubbel.pdf", p0];*)
(*ListLinePlot[resp, AxesOrigin\[Rule]{0,0}]
ListLinePlot[data, AxesOrigin\[Rule]{0,0}]
ListLinePlot[Re[OutputResponse[sys, Array[UnitStep,  sr]]], AxesOrigin\[Rule]{0,0}]*)












