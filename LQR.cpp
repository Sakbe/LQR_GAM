
//******************************************************************************
//
//		LQR.cpp - LQR CONTROL AND KALMAN FILTER
//		CORONA - CIANCIULLI 05/2019
//
//******************************************************************************

#include "LQR.h"

//OBJECTLOADREGISTER(IPID,"$Id: IPID.cpp,v 1.0 29/4/2011 14:22:36 ivoc Exp $")
// if cycle time is supplied
//CONSTRUCTOR AND DESTRUCTOR
LQR::LQR(){
	//this-> N_state = 10;
	//this-> N_input = 2;
	//this-> N_output = 2;

	this-> X_LQR = (float[N_state]){0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	this-> X_LQR_pos = (float[N_state]){-0.00685,	0.20752,	-0.16526,	-0.05566,	0.14089,	0.17667,	-0.12603,	0.08135,	-0.07533,	-0.04546};

	this-> X_LQR_neg = (float[N_state]){0, 0, 0, 0, 0, 0, 0, 0, 0, 0};


	this-> x_dot_pos = (float[N_state]){0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

	this-> x_pos = (float[N_state]){-0.005344092,	0.0520246,	-0.514431535,	1.150989527,	0.550062681,	-0.87777012,	0.308169602,	-0.356773408,	1.066604321,	-0.186231247};
	this-> x_pos = (float[N_state]){0.0191923,	0.289779,	0.309377,	0.0539503,	-0.2685851,	0.6644621,	-1.0757866,	-0.0274285,	0.1494512,	-0.3546514};
	this-> x_pos = (float[N_state]){-0.00685,	0.20752,	-0.16526,	-0.05566,	0.14089,	0.17667,	-0.12603,	0.08135,	-0.07533,	-0.04546};

			//this-> x_pos = (float[N_state]){-0.013195,	0.2031656,	0.3637952,	-0.9811761,	-0.8550528,	1.097347,	1.4067135,	0.5572165,	-1.3498684,	0.2045362};

	//this-> K_LQR_pos =(float[N_input * N_state]) {-39.8874724584811, -70.6769666120137, 354.869808121735, 370.159896447712, -106.569303855515, -10.6727031034049, -29.8250480200422, 75.3583282160950, -135.655340474040, -27.8586258177635,
	//						4.85034537803885, 16.3699444462248, -103.189045436383, -88.9493312103841, 36.1506690550597, 19.0337453517795, 10.4943236824918, -28.3848265454111, 45.6326833691854, 8.77044127460252};

		this-> A_est_pos= (float[N_state * N_state]) {0.696509123,	-0.042518988,	-0.012468926,	-0.003862841,	0.005098665,	-0.004452898,	0.000307541,	0.007529289,	0.000543772,	0.002729119,
-0.589110136,	-0.479267508,	0.086321563,	-0.169660121,	0.00540118,	-0.055694919,	-0.021127898,	0.018462067,	0.046097156,	0.075725421,
-5.345276833,	-0.756583393,	0.819592714,	0.06987188,	0.195200607,	-0.110207483,	-0.085320346,	0.314790487,	-0.05057786,	0.106414072,
0.704269886,	-0.517106116,	-0.04506851,	0.797865868,	0.127706274,	-0.09431041,	-0.125177503,	0.117920749,	0.226975054,	0.164094299,
-3.839459419,	1.240449309,	-0.171395287,	0.098771572,	0.993000031,	0.370617718,	0.265715957,	-0.162668273,	0.027881358,	-0.294598341,
6.199994564,	-0.02849404,	0.084329724,	0.006740028,	-0.357692689,	0.874269962,	0.217442542,	0.369150519,	-0.028065909,	0.190162316,
7.752907753,	3.111932993,	-0.1089129,	0.32372418,	-0.152577311,	-0.235800654,	0.310153306,	-0.488051772,	0.111269422,	0.314400196,
2.702347994,	6.669654846,	-0.472798735,	0.346363366,	0.009246062,	0.013148196,	0.559194624,	-0.125270218,	-0.601458132,	-0.111365497,
6.537444115,	4.441438198,	-0.18562147,	0.232780725,	-0.119777776,	-0.178793833,	0.202805638,	-0.100516535,	0.560188115,	-0.662117302,
-13.126461029,	-3.410126209,	-0.080644637,	-0.1100666,	0.118039578,	-0.179665551,	-0.467779845,	-0.067152724,	-0.423171699,	-0.167585224};

this-> B_est_pos=(float[N_state * ( N_input +  N_output)])  {-0.000006792,	-0.000128185,	-0.000056774,	0.000297621,	-0.00025856,	-0.000409708,	0.002094636,	-0.000586386,	-0.000392951,	-0.000140678,
-0.000008626,	-0.000150735,	0.000330579,	0.000499664,	-0.000642927,	-0.000565075,	0.001486448,	0.000295431,	0.000063408,	-0.001033877,
0.10402035,	5.2415452,	2.17423749,	1.510002494,	-5.00431633,	0.997147501,	-10.286964417,	-24.652036667,	-15.713902473,	11.225483894,
-0.54193759,	-2.40042901,	-9.543505669,	0.809700608,	-5.09362936,	10.185716629,	15.796350479,	11.094920158,	15.214260101,	-25.077713013};

	//B_est_pos =[vertical; horizonal; rc; zc]

	this-> C_est_pos=(float[N_state * (N_state +  N_output)])  {-0.019469423,	0.017150849,	-0.001723993,	0.001022543,	0.000459937,	0.000031242,	0.000176813,	0.000340432,	-0.000140771,	-0.000106723,
-0.050640617,	0.00015291,	-0.000937724,	0.000284173,	0.00057291,	-0.000264325,	0.000027612,	0.00033758,	0.000011572,	-0.000123955,
0.457547367,	-0.016828593,	-0.0085716,	0.002057274,	0.005877955,	-0.002974955,	0.000116215,	0.00338851,	0.00028086,	-0.001263967,
-1.106833458,	-0.032155037,	0.062108539,	-0.049119212,	-0.001998457,	-0.013826737,	-0.009465283,	-0.005383265,	0.009050866,	0.000869241,
-10.520903587,	0.981940627,	0.729384542,	0.109809786,	0.132349506,	-0.047529072,	0.01497573,	0.081844464,	-0.005668731,	-0.029036066,
-3.082989454,	2.359701633,	-0.244584695,	1.142890215,	0.067837201,	0.002178775,	0.024535369,	0.049518418,	-0.01926519,	-0.015668873,
-2.49770236,	-1.978803992,	0.112204932,	-0.092121467,	1.000403404,	-0.028478019,	-0.017952602,	-0.007829873,	0.017447438,	0.000750707,
-7.921667576,	-2.481028318,	0.053138226,	-0.089395292,	0.05449399,	0.93917948,	-0.020037837,	0.021935999,	0.023093147,	-0.010733564,
23.976324081,	10.54029274,	-0.402623981,	0.432528883,	-0.122432895,	0.207645729,	1.090120554,	-0.029038358,	-0.095648073,	0.022012381,
23.708824158,	-1.816794753,	0.578240812,	-0.226296037,	-0.292696178,	0.110184975,	-0.029897152,	0.820444167,	0.009409872,	0.06406416,
4.237761021,	-0.679330707,	0.13164261,	-0.059395768,	-0.057289399,	0.016938234,	-0.008791809,	-0.036464218,	1.0046947,	0.01267636,
-4.972575665,	-2.725485802,	0.126537815,	-0.11853072,	0.017827114,	-0.047258399,	-0.023936281,	-0.00062621,	0.024420552,	0.997299075};

this->C_inv_pos=(float[N_state*N_output]){-0.1128326,	-1.6521053,
					3.6955941,	-0.9863023,
					-0.2968683,	0.0484852,
					0.1980836,	-0.0436973,
					0.0530935,	0.0047902,
					0.0281362,	-0.0163292,
					0.0359928,	-0.0087381,
					0.0462931,	-0.0012036,
					-0.0313703,	0.0087999,
				-	0.0130463,	-0.0006182};


this-> D_est_pos=(float[(N_state + N_output) * (N_input + N_output)]) {0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
0.933653057,	-0.006654531,	-0.002363925,	3.719087601,	-4.928617477,	-9.176921844,	7.084938049,	8.307642937,	-36.456493378,	9.628709793,	3.044416189,	9.574270248,
-0.01511991,	0.916538477,	-0.912356317,	-2.852164507,	-16.396379471,	-2.747797251,	-6.088418007,	-15.542568207,	50.051330566,	37.342319489,	6.322620869,	-10.915969849};

//	this-> N_BAR_pos = (float[N_input +  N_output]){-16738.8719868375, 3479.82442345434,
//							488.651395096507, -28.3958381254954};



	//more slow
	this-> N_BAR_pos = (float[N_input +  N_output]){1324.4936648,	-3781.71519,
							5627.5062401,	947.5168105};

		this-> N_BAR_pos = (float[N_input +  N_output]){5853.8240915,	-13055.372391,
														4594.5643019,	3609.2329171};
this-> N_BAR_pos = (float[N_input +  N_output]){-3598.6524657,	-1765.8794033,
																									7780.624649,	494.1986186};



	this-> K_LQR_pos =(float[N_input * N_state]) {3700.2519778,	-352.6458013,	-113.7109751,	31.1419703,	-25.2673037,	-136.5708496,	16.8915749,	-65.2971081,	172.4054825,	-111.1846448,
						      -378.759192,	23.8683873,	49.1286694,	38.0276358,	61.7983902,	-42.3959233,	30.2818625,	-24.4788253,	100.1365539,	-53.1858175};

this-> K_LQR_pos =(float[N_input * N_state]) {9989.8209768,	-478.4496862,	-211.4326002,	-178.1454089,	-33.2752205,	-239.4939687,	78.5969423,	-156.2937366,	306.662527,	-213.3528498,
						-2038.9472632,	-11.4097386,	121.0765111,	51.6192656,	75.3742932,	-32.1506706,	31.9659901,	-18.6252239,	94.5317454,	-54.1750745};
this-> K_LQR_pos =(float[N_input * N_state]) {1798.9164354,	-249.9623466,	-60.4474019,	47.4826995,	-12.1942119,	-74.7579493,	8.5088559,	-34.4346594,	102.0502044,	-64.5773612,
221.3566477,	-43.055835,	28.9855292,	47.6550393,	56.8664503,	-62.4013802,	32.3628063,	-33.9012196,	126.1440117,	-69.8926029};



	this-> x_neg=(float[N_state])  {-0.01322152646,	0.21257243483,	0.24681826366,	-0.33280829935,	-0.00461930354,	0.02045689304,	-0.05335478233,	0.02913866606,	-0.38100515631,	-0.01904457052};
	this-> x_neg=(float[N_state])  {-0.1219579,	0.1357889,	0.8427376,	-0.3916806,	0.3457801,	0.0998817,	-0.0734193,	0.0101452,	-0.4403928,	-0.3972219};


	this-> x_dot_neg=(float[N_state])  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
//	this-> K_LQR_neg=(float[N_input * N_state])  {-1.10243700688381, -26.6888168111469, 248.208386299799, 2272.69314089294, 341.435985384170, 116.974185358079, -1571.00753489878, -331.351679250269, -1271.06969797964, -4441.09340489016,
//							-0.233414809301534, -21.1374545809135, 237.120488501101, 3170.68925311282, -143.026532612836, 258.466914847382, -1451.21045848359, -298.057584698670, -925.765520002125, -4247.87411829111};


this-> A_est_neg=(float[N_state * N_state]){0.771434903,	-0.021348163,	0.026153579,	-0.003034116,	0.00033719,	0.005463117,	0.008698117,	0.001348557,	-0.001405753,	-0.005695,
-0.366069525,	0.250144333,	0.001444294,	-0.067050375,	-0.00747909,	-0.046246402,	0.074281342,	-0.063517481,	-0.077964701,	-0.021003148,
4.335814953,	-0.590004861,	0.597714961,	-0.014256048,	0.061607752,	-0.135960534,	-0.082231559,	-0.145310953,	-0.07786762,	0.105946757,
-0.549529731,	-0.505382001,	-0.01467749,	0.903384328,	0.113554217,	0.013634915,	0.116127744,	-0.001548065,	-0.129825935,	-0.025932135,
-6.09044838,	-0.046373639,	0.166769952,	-0.164827242,	0.951034069,	0.334019393,	-0.070105106,	0.032830406,	-0.039465945,	-0.072917856,
-2.646726131,	-1.392825127,	0.135581598,	-0.017703824,	-0.359038204,	0.903093755,	0.00646944,	-0.189019114,	-0.071997091,	0.033450905,
2.133527994,	2.22832036,	0.021729587,	0.042188793,	0.052367792,	0.019750303,	0.83642447,	0.234644026,	0.059001833,	0.321341515,
0.096559733,	-0.928759277,	0.002022055,	-0.028890036,	-0.112281762,	0.043850061,	-0.269708097,	0.819548965,	-0.468864441,	0.17143555,
-0.25124827,	1.261878371,	0.134749249,	0.002615248,	0.035810255,	0.022211017,	-0.044809174,	0.296370924,	0.880721569,	-0.150740668,
3.595902443,	-0.37080878,	-0.199803695,	0.015529932,	-0.002768105,	-0.041213844,	-0.194448233,	-0.153701216,	0.084358327,	0.940047324};


this-> B_est_neg=(float[N_state * ( N_input +  N_output)]) {-0.00001070484,	-0.00018352285,	-0.00003740476,	-0.00016039671,	-0.00002731199,	-0.00028521486,	0.00069076713,	0.00005484348,	0.00036286309,	-0.0000075353,
0.00000686852,	0.00057635334,	0.00029789837,	0.00083011913,	0.00079056883,	0.00058172137,	-0.00060404028,	0.00136100687,	0.00043902177,	-0.00052344694,
0.09232706577,	3.0948278904,	2.15514469147,	2.06601238251,	0.90465670824,	6.51248788834,	-9.77792072296,	4.19905138016,	-5.75626945496,	1.2126326561,
1.07229363918,	0.35713252425,	-22.09178352356,	1.69208729267,	29.16925430298,	9.78439331055,	-5.65546703339,	-2.42480802536,	3.98085331917,	-18.06007766724};


this-> C_est_neg=(float[N_state * (N_state +  N_output)]) {0.117056169,	0.026251998,	-0.003811811,	-0.000269252,	0.000071083,	-0.000344695,	0.000170941,	-0.000610935,	-0.00031992,	0.000382334,
0.1303069,	-0.002285592,	-0.005423918,	-0.000344409,	0.000059554,	-0.000417361,	-0.000087633,	-0.000634914,	-0.000244024,	0.000796742,
0.783260882,	-0.027212553,	0.00785953,	0.00052888,	-0.000118324,	0.000661077,	-0.000127797,	0.001100519,	0.000516234,	-0.000959923,
0.121271349,	0.125358284,	-0.037739728,	-0.001557684,	-0.000486643,	-0.001320118,	-0.007777475,	0.000660145,	0.002877327,	0.011018277,
4.491700172,	-0.507688284,	0.796966255,	-0.01248,	0.001786376,	-0.014844493,	-0.006803832,	-0.021270597,	-0.006885507,	0.032515604,
0.954077303,	-0.712801874,	-0.06579335,	0.996491373,	0.000003596,	-0.003799102,	-0.006781216,	-0.003650652,	0.000689936,	0.014032086,
-4.158698082,	0.410507441,	0.18575041,	0.011470341,	0.998309076,	0.013680383,	0.00577423,	0.019779028,	0.006586887,	-0.029403677,
-4.391922474,	-1.145311236,	0.137010559,	0.009874942,	-0.002766647,	1.012761712,	-0.007827932,	0.023152038,	0.012573844,	-0.012456535,
-1.097618341,	2.447838783,	0.136683211,	0.006344616,	0.001007164,	0.006108885,	1.022159219,	0.001865919,	-0.006585477,	-0.035315961,
-1.920884728,	0.568216145,	0.099983096,	0.005834932,	-0.000545818,	0.006723195,	0.006006531,	1.008592963,	0.00169537,	-0.018040769,
-0.712583721,	1.432452202,	0.082864389,	0.003896785,	0.000556503,	0.003798607,	0.013003765,	0.001436061,	0.99628222,	-0.021081693,
3.456563711,	0.012501119,	-0.141136557,	-0.009032226,	0.001625186,	-0.010992962,	-0.001679561,	-0.016946778,	-0.006733265,	1.020273328};


this->C_inv_neg=(float[N_state*N_output]){0.1402455,	4.7841462,
					4.376472,	-2.0959448,
					0.1582349,	-0.2745241,
					0.0058383,	-0.0154977,
					0.0027846,	0.0009365,
					0.0042268,	-0.0174717,
					0.0385296,	-0.0209643,
					-0.006962,	-0.0204256,
					-0.015843,	-0.0018004,
					-0.0507191,	0.0529503};

this-> D_est_neg=(float[(N_state + N_output) * (N_input + N_output)]){0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
0.869301736,	-0.007374771,	0.148214549,	3.817733765,	1.625854492,	2.997158289,	-1.244319558,	5.606616497,	-10.583392143,	-2.234328032,	-6.183921814,	-0.516182721,
-0.506077468,	0.370243132,	0.982124746,	-2.424515486,	-22.611539841,	-6.077579498,	20.809724808,	18.650072098,	10.421789169,	10.409658432,	6.435731411,	-16.551050186};



//	this-> N_BAR_neg=(float[N_input +  N_output]) {6692.27395164254, -960.635617013133,
	//						-2256.41280370701, -489.068332481912};


	//more slow
	this-> N_BAR_neg = (float[N_input +  N_output]){14556.4457346,	-163150.2148227,
							-1084.9066485,	-91867.0705769};
	this-> N_BAR_neg = (float[N_input +  N_output]){6474.6710386,	-26883.6520523,
							-2977.2307276,	-378.189811};



	this-> K_LQR_neg =(float[N_input * N_state]) {-31251.0588123,	1414.0766893,	-853.434623,	-658.1456663,	-502.2072764,	-953.4037428,	-42.8599327,	762.4519004,	1250.1742874,	-1214.7263428,
-19418.4120212,	1325.6479719,	-1341.7580667,	358.9898259,	293.0645403,	-128.6368865,	-42.539771,	221.3635038,	43.4667236,	-104.5534523};

this-> K_LQR_neg =(float[N_input * N_state]) {-2422.3685673,	298.3522858,	-99.9464706,	312.1853208,	178.6849199,	-697.4033763,	912.4471051,	471.0257494,	289.2460828,	304.0203188,
-616.631363,	3.7306498,	-92.3733463,	-4.8295012,	205.8074232,	-52.1753129,	-63.7909858,	120.9179473,	-60.7865787,	-134.1598887};



}

LQR::~LQR(){
}




//////////////////////////// Controllers /////////////////////////////////////////////////////////


//////////////////////////// Controllers /////////////////////////////////////////////////////////


LQRouputs  LQR::MIMO_CONTROL_POSITIVE(float R_ref, float Z_ref, float R_real, float Z_real, float I_vertical, float I_horizontal){
	float u_Nbar_0 = 0;
	float u_Nbar_1 = 0;
	float u_vertical=0;
	float u_horizontal=0;
	int i = 0;
	int j = 0;
	float temp = 0.0;
	float *outputs;
	outputs =(float[2]) {0, 0};
	LQRouputs Outputs={0,0};



	//Nbar(2x2)
	u_Nbar_0 = (R_ref* this->N_BAR_pos[0]) + (Z_ref* this->N_BAR_pos[1]);
	u_Nbar_1 = (R_ref * this->N_BAR_pos[2]) + (Z_ref * this->N_BAR_pos[3]);

	//u=u-k_lqr*x
	for (i = 0; i < N_state; i++) {
		temp += this->X_LQR_pos[i] * this->K_LQR_pos[i];
		}
	u_vertical = u_Nbar_0 - temp;
	temp = 0;

	for (i = 0; i < N_state; i++) {
		temp += this->X_LQR_pos[i] * this->K_LQR_pos[i+N_state];

	}
	u_horizontal = u_Nbar_1 - temp;
	temp = 0;

	Outputs.Ivert = u_vertical;
	Outputs.Ihor = u_horizontal;

	return Outputs;
}


LQRouputs  LQR::MIMO_CONTROL_NEGATIVE(float R_ref, float Z_ref, float R_real, float Z_real, float I_vertical, float I_horizontal){
	float u_Nbar_0 = 0;
	float u_Nbar_1 = 0;
	float u_vertical=0;
	float u_horizontal=0;
	int i = 0;
	int j = 0;
	float temp = 0.0;
	float *outputs;
	outputs =(float[2]) {0, 0};
	LQRouputs Outputs={0,0};



	//Nbar(2x2)
	u_Nbar_0 = (R_ref* this->N_BAR_neg[0]) + (Z_ref* this->N_BAR_neg[1]);
	u_Nbar_1 = (R_ref * this->N_BAR_neg[2]) + (Z_ref * this->N_BAR_neg[3]);

	//u=u-k_lqr*x
	for (i = 0; i < N_state; i++) {
		temp += this->X_LQR_neg[i] * this->K_LQR_neg[i];
	}
	u_vertical = u_Nbar_0 - temp;
	temp = 0.0;

	for (i = 0; i < N_state; i++) {
		temp += this->X_LQR_neg[i] * this->K_LQR_neg[i+N_state];

	}
	u_horizontal = u_Nbar_1 - temp;
		temp = 0.0;

	Outputs.Ivert = u_vertical;
	Outputs.Ihor = u_horizontal;

	return Outputs;
}




///////////////////////////////////////////// KALMAN FILTERS////////////////////////////////////////////////////////





Kalman LQR:: KALMAN_FILTER_POS(float R_real, float Z_real, float I_vertical, float I_horizontal, int sign){
	//the same as before
	//if we use this in mimo class we can comment from 102 to 115
	//i putted because we can copy this in IPID class
	float temp=0.0;
	int j=0;
	int i=0;
	int m=0;
	int n=0;
	// buffers time

	float buff=0.0;
	float buffer=0.0;


	float* y_est;
	y_est =(float[2]){0, 0};
	float* X_est;
	X_est =(float[10]){0, 0,0,0,0,0,0,0,0,0};


	Kalman Outputs={0.085,0.085,X_est};


	buff=0.0;

	if(sign == 1){

		for(j = 0; j < N_state; j++){
			buff = 0.0;
			for (i = 0; i < N_state; i++) {
				m=i + j*(N_state);
				buff = buff + this->A_est_pos[m] * this->x_pos[i];
			}
			this->x_dot_pos[j] = buff;
		}

		for(i = 0; i < N_state; i++){
			j= i + (N_state);
			m=i + 2*(N_state);
			n=i + 3*(N_state);
			temp =  this->B_est_pos[i] * I_vertical + this->B_est_pos[j] * I_horizontal + this->B_est_pos[m] * R_real + this->B_est_pos[n] * Z_real;
			this->x_dot_pos[i] += temp;

		}
		temp = 0.0;

		//x^(k+1) = A_est * x(k)+ B_est * u(k)

		//[y_est x_est] = C_est x_est + D_est [u_real y_real]
		for(j = 0; j < N_output; j++){
			buff = 0.0;
			for (i = 0; i < N_state; i++) {
				m=i + j*(N_state);
				 buff += this->C_est_pos[m] * this->x_pos[i];
			}
			y_est[j] = buff;
		}



			buff =  this->D_est_pos[24] * R_real + this->D_est_pos[36] * Z_real;
			y_est[0] += buff;
			buff = 0.0;
			buff =  this->D_est_pos[25] * R_real + this->D_est_pos[37] * Z_real;
			y_est[1] += buff;
			buff = 0.0;






			//x(k)=x(k+1) for the next step


		Outputs.Kalman_R= y_est[0];
		Outputs.Kalman_Z= y_est[1];
		Outputs.X_est= this-> x_pos;

		buffer = 0.0;
		for (i = 0; i < N_state; i++) {
			buffer =this->x_dot_pos[i];
			this->x_pos[i]=buffer;
		}

			for(i=0; i< N_state; i++){
		buff = this->x_pos[i];
		this->X_LQR_pos[i] = buff;
	}

		}else{
			Outputs.Kalman_R= 0.085;
			Outputs.Kalman_Z= 0.085;
				for (i = 0; i < N_state; i++) {
						X_est[i]=0.0;}

			Outputs.X_est=X_est;
			}


	return Outputs;

}

Kalman LQR:: KALMAN_FILTER_NEG(float R_real, float Z_real, float I_vertical, float I_horizontal, int sign){
	//the same as before
	//if we use this in mimo class we can comment from 102 to 115
	//i putted because we can copy this in IPID class
	float temp=0.0;
	int j=0;
	int i=0;
	int m=0;
	int n=0;
	// buffers time

	float buff=0.0;
	float buffer=0.0;


	float* y_est;
	y_est =(float[2]){0, 0};
	float* X_est;
	X_est =(float[10]){0, 0,0,0,0,0,0,0,0,0};
	Kalman Outputs={0.085,0.085,X_est};


	buff=0.0;
	if(sign == 1){

		for(j = 0; j < N_state; j++){
			buff = 0.0;
			for (i = 0; i < N_state; i++) {
				m=i + j*(N_state);
				buff = buff + this->A_est_neg[m] * this->x_neg[i];
			}
			this->x_dot_neg[j] = buff;
		}

		for(i = 0; i < N_state; i++){
			j= i + (N_state);
			m=i + 2*(N_state);
			n=i + 3*(N_state);
			temp =  this->B_est_neg[i] * I_vertical + this->B_est_neg[j] * I_horizontal + this->B_est_neg[m] * R_real + this->B_est_neg[n] * Z_real;
			this->x_dot_neg[i] += temp;

		}
		temp = 0.0;



		//[y_est x_est] = C_est x_est + D_est [u_real y_real]
		for(j = 0; j < N_output; j++){
			buff = 0.0;
			for (i = 0; i < N_state; i++) {
				m=i + j*(N_state);
				 buff += this->C_est_neg[m] * this->x_neg[i];
			}
			y_est[j] = buff;
		}



			buff =  this->D_est_neg[24] * R_real + this->D_est_neg[36] * Z_real;
			y_est[0] += buff;
			buff = 0.0;
			buff =  this->D_est_neg[25] * R_real + this->D_est_neg[37] * Z_real;
			y_est[1] += buff;
			buff = 0.0;




			//x(k)=x(k+1) for the next step


		Outputs.Kalman_R= y_est[0];
		Outputs.Kalman_Z= y_est[1];
		Outputs.X_est=this->x_neg;

		buffer = 0.0;
		for (i = 0; i < N_state; i++) {
			buffer =this->x_dot_neg[i];
			this->x_neg[i]=buffer;
		}

				for(i=0; i< N_state; i++){
				buff = this->x_neg[i];
				this->X_LQR_neg[i] = buff;
				}

		}else{
			Outputs.Kalman_R= 0.085;
			Outputs.Kalman_Z= 0.085;
				for (i = 0; i < N_state; i++) {
						X_est[i]=0.0;}

			Outputs.X_est=X_est;
			}


	return Outputs;

}
int LQR:: erase(float R_real, float Z_real) {
	int i = 0;
	float* state0_pos;
	float* state0_neg;
	state0_pos = (float[N_state]){-0.005344092,	0.0520246,	-0.514431535,	1.150989527,	0.550062681,	-0.87777012,	0.308169602,	-0.356773408,	1.066604321,	-0.186231247};
	state0_pos = (float[N_state]){0.0191923,	0.289779,	0.309377,	0.0539503,	-0.2685851,	0.6644621,	-1.0757866,	-0.0274285,	0.1494512,	-0.3546514};
	state0_pos = (float[N_state]){	0.0075 ,   0.2071 ,  -0.0394  , -0.1344  , -0.0625   , 0.4041  , -0.5053 ,   0.0973  ,  0.2590,   -0.0032};
	state0_pos = (float[N_state]){-0.00685,	0.20752,	-0.16526,	-0.05566,	0.14089,	0.17667,	-0.12603,	0.08135,	-0.07533,	-0.04546};


	state0_neg=(float[N_state])  {-0.01322152646,	0.21257243483,	0.24681826366,	-0.33280829935,	-0.00461930354,	0.02045689304,	-0.05335478233,	0.02913866606,	-0.38100515631,	-0.01904457052};
	state0_neg=(float[N_state])  {-0.1219579,	0.1357889,	0.8427376,	-0.3916806,	0.3457801,	0.0998817,	-0.0734193,	0.0101452,	-0.4403928,	-0.3972219};

	for (i = 0; i < N_state; i++) {
			this->x_dot_pos[i]=0.0;
		}
	for (i = 0; i < N_state; i++) {
			this->x_dot_neg[i]=0.0;
		}
	for (i = 0; i < N_state; i++) {
			this->x_pos[i]=state0_pos[i];
		}
	for (i = 0; i < N_state; i++) {
			this->x_neg[i]=state0_neg[i];
		}
	//for (i = 0; i < N_state; i++) {
			//this->x_pos[i]=this->C_inv_pos[N_output*i]*R_real + this->C_inv_pos[1+N_output*i]*Z_real;
			//this->X_LQR_pos[i]=this->C_inv_pos[N_output*i]*R_real + this->C_inv_pos[1+N_output*i
			//]*Z_real;
		//}
	//for (i = 0; i < N_state; i++) {
		//this->x_neg[i]=this->C_inv_neg[N_output*i]*R_real + this->C_inv_neg[1+N_output*i]*Z_real;
		//this->X_LQR_neg[i]=this->C_inv_neg[N_output*i]*R_real + this->C_inv_neg[1+N_output*i]*Z_real;

		//}

	return 1;
	}


	/* POSITIVE
	/////normal
	this-> N_BAR_pos = (float[N_input +  N_output]){-16738.8719868375, 3479.82442345434,
							488.651395096507, -28.3958381254954};
	this-> K_LQR_pos =(float[N_input * N_state]) {-39.8874724584811, -70.6769666120137, 354.869808121735, 370.159896447712, -106.569303855515, -10.6727031034049, -29.8250480200422, 75.3583282160950, -135.655340474040, -27.8586258177635,
							4.85034537803885, 16.3699444462248, -103.189045436383, -88.9493312103841, 36.1506690550597, 19.0337453517795, 10.4943236824918, -28.3848265454111, 45.6326833691854, 8.77044127460252};
	/////slow
	this-> N_BAR_pos = (float[N_input +  N_output]){-11086.5128004769, 2304.91025662465,
							-624.913612903589, 203.085650822326};
	this-> K_LQR_pos =(float[N_input * N_state]) {-8.01681293888861, -26.8325522087463, 134.585605910785, 71.3907687002046, -31.1613639245902, 1.06653823136754, -8.67641023817368, 30.6278817417476, -52.6867168563030, -17.6236782619040,
							-0.359505258997209, 5.27976739349132, -34.7284975804598, -24.9860321020505, 10.5336478520904, 3.20301260401835, 2.98116013872604, -9.62426558998255, 15.6891220336232, 4.25997674316981};


	//more slow
	this-> N_BAR_pos = (float[N_input +  N_output]){-10292.2693526553, 2133.74129809333,
							-944.140351815484, 269.810568562941};
	this-> K_LQR_pos =(float[N_input * N_state]) {-0.677239930551175, -5.56445051715661, 29.1530400398665, 10.5689835482429, -6.43042836144154, 0.784006911127944, -1.67848331436731, 6.89611601694075, -11.6198347798690, -4.41024916164279,
							-0.253637909222695, 0.998896201615173, -6.91291373508615, -4.34730845911924, 2.02654430640833, 0.350198601401546, 0.540286005706202, -1.95918796444674, 3.18376611395890, 0.992300688479676};

	*/
	/* NEGATIVE
	//////normal
	this-> K_LQR_neg=(float[N_input * N_state])  {-1.10243700688381, -26.6888168111469, 248.208386299799, 2272.69314089294, 341.435985384170, 116.974185358079, -1571.00753489878, -331.351679250269, -1271.06969797964, -4441.09340489016,
							-0.233414809301534, -21.1374545809135, 237.120488501101, 3170.68925311282, -143.026532612836, 258.466914847382, -1451.21045848359, -298.057584698670, -925.765520002125, -4247.87411829111};
	this-> N_BAR_neg=(float[N_input +  N_output]) {6692.27395164254, -960.635617013133,
							-2256.41280370701, -489.068332481912};

	/////slow
	this-> N_BAR_pos = (float[N_input +  N_output]){6589.72680834879, -954.006515986846,
							-2507.09039980905, -438.508741661756};
	this-> K_LQR_pos =(float[N_input * N_state]) {-0.140009763339089, -3.18557215603840, 30.5815322306256, 261.182404835037, 41.0701964065595, 15.1457297490992, -184.071391002032, -37.9502637307121, -150.255931786410, -524.709987410739,
							-0.0430382829459303, -2.40364558484570, 28.2516724393487, 349.930303853398, -19.3580296640594, 27.8929619552656, -166.244389576828, -34.2340029306290, -102.365591295273, -474.430220412449};


	//more slow
	this-> N_BAR_pos = (float[N_input +  N_output]){6577.20274262693, -953.521247320254,
							-2537.02933847542, -432.837113235285};
	this-> K_LQR_pos =(float[N_input * N_state]) {-0.0143959540956107, -0.325150394017629, 3.13416013810849, 26.5396916000373, 4.19324806144036, 1.55806909562497, -18.7468162690424, -3.85545880019961, -15.3160343140834, -53.4859040919299,
							-0.00458150757613837, -0.243881430718078, 2.88347865234915, 35.3882054725928, -2.01002787695297, 2.81135503841810, -16.8859632308927, -3.47894536276546, -10.3473795912101, -48.0323686610169};

	*/
