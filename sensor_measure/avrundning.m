(* ::Package:: *)

ClearAll["Global`*"]
sr = 100;
data = 1023 -Import["~/kandikod/m\[ADoubleDot]tdata/flex", "List"];
(*datapostDouble = Import["~/kandikod/m\[ADoubleDot]tdata/samples_filter_float", "List"];*)
datapostInt = Import["~/kandikod/m\[ADoubleDot]tdata/flex_unit", "List"];

ListLinePlot[{data, datapostInt}
, AxesOrigin->{0,0}
, PlotRange->Full
, DataRange->{0, Length[data]/sr}
, ImageSize->418
]

