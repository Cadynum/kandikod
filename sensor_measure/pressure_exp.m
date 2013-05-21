(* ::Package:: *)

ClearAll["Global`*"]
SetOptions[{Plot,ParametricPlot, ListLinePlot, ListPlot},BaseStyle->{FontFamily->"Latin Modern Roman", FontSize->11}];
pekfingerold={{0.5,400},{1,450},{1.5,520},{2,550},{2.5,582},{3,600},{3.5,615},{4,631},{4.5,640},{5,652},{5.5,666},{6,672},{6.5,683},{7,691},{7.5,702}};
pekfinger = {{0    , 0},
{0.5  , 23},
{1    , 27},
{1.5  , 34},
{2    , 62},
{2.5  , 143},
{3    , 216},
{3.5  , 249},
{4    , 284},
{4.5  , 305},
{5    , 360},
{5.5  , 386},
{6    , 407},
{6.5  , 434},
{7    , 449},
{7.5  , 460},
{8    , 470},
{8.5  , 475},
{9    , 484},
{9.5  , 499},
{10   , 529}};
langfinger={{0,0},{0.5,37},{1,112},{1.5,207},{2,261},{2.5,318},{3,354},{3.5,387},{4,405},{4.5,422},{5,445},{5.5,470},{6,482},{6.5,500},{7,505},{7.5,514},{8,527},{8.5,543},{9,558},{9.5,563},{10,578}};
tumme={{0,0}, {0.5,0},{1,112},{1.5,217},{2,295},{2.5,380},{3,420},{3.5,455},{4,476},{4.5,500},{5,522},{5.5,538},{6,555},{6.5,571},{7,585},{7.5,595},{8,600},{8.5,611},{9,617},{9.5,625},{10,630}};

langopt = {285, 1.42, 0.305};
tummeopt = {381, 1.7, 0.22};
pekfingeropt = {286, 2.81, 0.271};

finger = pekfinger;
opt  = pekfingeropt;

langinv = Reverse /@ finger;
f[x_, a_, b_ ,d_] := a(1-Exp[-(x)/b]) * x^d;
inv[y_,a_,b_, d_] := x /. FindRoot[y == f[x,a,b,d], {x, 0, 1023}]
(*	fe = a(1-Exp[-(x)/b]);
	fr = c*x^d;*)
Manipulate[
	p1 = Plot[f[x, a, b, d] , {x, 0, 20}, PlotRange->Automatic];
	p2 = ListPlot[finger];
	
	pi1 = Plot[inv[x,a,b,d], {x, 0, 1024}];
	pi2 = ListPlot[langinv];

	s1 = Show[ p1,p2
			, AxesOrigin->{0,0}
			, PlotRange->{0, 1023}
			, AxesLabel->{"Kraft (N)", "Sensor"}
			, ImageSize->350
			];
	s2 = Show[ pi1, pi2
			, AxesOrigin -> {0,0}
			, PlotRange -> {{0, 1024}, {0, 20}}
			, AxesLabel->{"Sensor", "Kraft (N)"}
			, ImageSize->350
		];
(*	Export["~/kandidat/Slutrapport/img/tryck/before.pdf", s1];
	Export["~/kandidat/Slutrapport/img/tryck/after.pdf", s2];*)
	GraphicsColumn[{s1, s2}]
	, {{a, opt[[1]]}, 1, 1023}, {{b, opt[[2]]}, 0.01, 10}, {{d, opt[[3]]}, 0.01, 1}
]

Table[inv[n, opt[[1]], opt[[2]], opt[[3]]], {n, 0, 1023}];
Export["~/kandikod/m\[ADoubleDot]tdata/tryckinvers/pekfinger.m", %]



