(* ::Package:: *)

ClearAll["Global`*"]
sr = 100;
data = 1023 -Import["~/kandikod/m\[ADoubleDot]tdata/samples", "List"];
datapostDouble = Import["~/kandikod/m\[ADoubleDot]tdata/samples_filter_float", "List"];
datapostInt = Import["~/kandikod/m\[ADoubleDot]tdata/samples_filter_uint", "List"];

ListLinePlot[Abs[datapostInt - datapostDouble]
, AxesOrigin->{0,0}
, PlotRange->Full
, DataRange->{0, Length[data]/sr}
, ImageSize->418
]

