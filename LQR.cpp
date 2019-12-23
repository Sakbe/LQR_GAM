
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
	this-> X_LQR_pos = (float[N_state]){-0.00794,	0.08333,	-0.32369,	-0.20072,	0.35133,	-0.03818,	0.82502,	0.03578,	-0.12314,	0.00307};
	//this-> X_LQR_pos = (float[N_state]){-0.00338,	0.14165,	-0.1744,	-0.54187,	-0.27558,	0.13963,	1.61163,	0.23229,	-0.83422,	-0.13946};
	//this-> X_LQR_pos = (float[N_state]){-0.00566913759758476,	0.121490081315979,	0.0409696382595862,	-0.326033663487195,	-0.132618254130713,	0.145414194373366,	0.640709770994902	,0.220661833695255	,-0.375976754083591,	-0.0476667263059292};

	this-> X_LQR_neg = (float[N_state]){0.032456363499452,	-0.063785306076201,	0.124571869100746,	-0.065387443522556,	0.093090988857802,	-1.40440635057351,	-0.320533077979534,	0.246014136258589,	-0.076864950567127,	0.599032477284996};
	this-> X_LQR_neg = (float[N_state]){0.054207867846701,	-0.052337115646198,	0.038441642608233,	-0.034164545243869,	0.218126249484017,	0.24417046356667,	-0.322416522481022,	-0.066889754294555,	-0.389451884260603,	0.278935578024248};
	this-> X_LQR_neg = (float[N_state]){0.016810611810391,	-0.078703906791538,	0.209254630418628,	0.03556454476693,	0.083981660502173,	-0.683348686404463,	-0.213786377122719,	0.177045937944626,	-0.252841577523042,	0.709383785099129};
	this-> X_LQR_neg = (float[N_state])	{0.0555035358095847,	-0.0129555570766988,	0.00523003615303577	,-0.0290025216580580	,0.0624195965501496	-0.169313794694064,	0.144650598039852	,0.00366822605174714,	-0.0505172707740238,	-0.098042187340031};
	this-> X_LQR_neg = (float[N_state])	{0.011489721761823,	-0.103275605316704,	0.230889418040253,	0.080085093022331,	-0.075841805411825,	-0.830726272789686,	-0.13293929661096,	0.338417479411358,	-0.251475684125608,	0.935264122858397};
	this-> X_LQR_neg = (float[N_state])	{-0.009741366241305,	-0.205912818018256,	0.198602091754336,	0.070552052210391,	0.219878908860687,	-0.289459715701652,	-0.249161976447696,	0.085702144441041,	-0.306982640761359,	0.246668394499494};
	this-> X_LQR_neg = (float[N_state])	{0.048686371278709,	-0.060937894056835,	-0.044287248204942,	-0.069077880371761,	0.099010490176201,	0.188131610082302,	-0.054100669322058,	-0.139779569622899,	-0.224157306520685,	-0.095990081022785};


	this-> x_dot_pos = (float[N_state]){0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

	this-> x_pos = (float[N_state]){-0.005344092,	0.0520246,	-0.514431535,	1.150989527,	0.550062681,	-0.87777012,	0.308169602,	-0.356773408,	1.066604321,	-0.186231247};
	this-> x_pos = (float[N_state]){-0.00338,	0.14165,	-0.1744,	-0.54187,	-0.27558,	0.13963,	1.61163,	0.23229,	-0.83422,	-0.13946};

	this-> x_pos = (float[N_state]){-0.00794,	0.08333,	-0.32369,	-0.20072,	0.35133,	-0.03818,	0.82502,	0.03578,	-0.12314,	0.00307};
	//this-> x_pos = (float[N_state]){-0.00566913759758476,	0.121490081315979,	0.0409696382595862,	-0.326033663487195,	-0.132618254130713,	0.145414194373366,	0.640709770994902	,0.220661833695255	,-0.375976754083591,	-0.0476667263059292};

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
//this-> N_BAR_pos = (float[N_input +  N_output]){-3598.6524657,	-1765.8794033,
	//																								7780.624649,	494.1986186};



	this-> K_LQR_pos =(float[N_input * N_state]) {3700.2519778,	-352.6458013,	-113.7109751,	31.1419703,	-25.2673037,	-136.5708496,	16.8915749,	-65.2971081,	172.4054825,	-111.1846448,
						      -378.759192,	23.8683873,	49.1286694,	38.0276358,	61.7983902,	-42.3959233,	30.2818625,	-24.4788253,	100.1365539,	-53.1858175};

this-> K_LQR_pos =(float[N_input * N_state]) {9989.8209768,	-478.4496862,	-211.4326002,	-178.1454089,	-33.2752205,	-239.4939687,	78.5969423,	-156.2937366,	306.662527,	-213.3528498,
						-2038.9472632,	-11.4097386,	121.0765111,	51.6192656,	75.3742932,	-32.1506706,	31.9659901,	-18.6252239,	94.5317454,	-54.1750745};
//this-> K_LQR_pos =(float[N_input * N_state]) {1798.9164354,	-249.9623466,	-60.4474019,	47.4826995,	-12.1942119,	-74.7579493,	8.5088559,	-34.4346594,	102.0502044,	-64.5773612,
//221.3566477,	-43.055835,	28.9855292,	47.6550393,	56.8664503,	-62.4013802,	32.3628063,	-33.9012196,	126.1440117,	-69.8926029};



		this-> x_neg=(float[N_state])  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	this-> x_neg=(float[N_state])  {0.032456363499452,	-0.063785306076201,	0.124571869100746,	-0.065387443522556,	0.093090988857802,	-1.40440635057351,	-0.320533077979534,	0.246014136258589,	-0.076864950567127,	0.599032477284996};
	this-> x_neg=(float[N_state])  {0.054207867846701,	-0.052337115646198,	0.038441642608233,	-0.034164545243869,	0.218126249484017,	0.24417046356667,	-0.322416522481022,	-0.066889754294555,	-0.389451884260603,	0.278935578024248};
	this-> x_neg=(float[N_state])  {0.016810611810391,	-0.078703906791538,	0.209254630418628,	0.03556454476693,	0.083981660502173,	-0.683348686404463,	-0.213786377122719,	0.177045937944626,	-0.252841577523042,	0.709383785099129};
	this-> x_neg=(float[N_state])  {0.0555035358095847,	-0.0129555570766988,	0.00523003615303577	,-0.0290025216580580	,0.0624195965501496	-0.169313794694064,	0.144650598039852	,0.00366822605174714,	-0.0505172707740238,	-0.098042187340031};
		this-> x_neg=(float[N_state])  {0.011489721761823,	-0.103275605316704,	0.230889418040253,	0.080085093022331,	-0.075841805411825,	-0.830726272789686,	-0.13293929661096,	0.338417479411358,	-0.251475684125608,	0.935264122858397};
		this-> x_neg=(float[N_state])  {-0.009741366241305,	-0.205912818018256,	0.198602091754336,	0.070552052210391,	0.219878908860687,	-0.289459715701652,	-0.249161976447696,	0.085702144441041,	-0.306982640761359,	0.246668394499494};
		this-> x_neg=(float[N_state])  {0.048686371278709,	-0.060937894056835,	-0.044287248204942,	-0.069077880371761,	0.099010490176201,	0.188131610082302,	-0.054100669322058,	-0.139779569622899,	-0.224157306520685,	-0.095990081022785};



	this-> x_dot_neg=(float[N_state])  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
//	this-> K_LQR_neg=(float[N_input * N_state])  {-1.10243700688381, -26.6888168111469, 248.208386299799, 2272.69314089294, 341.435985384170, 116.974185358079, -1571.00753489878, -331.351679250269, -1271.06969797964, -4441.09340489016,
//							-0.233414809301534, -21.1374545809135, 237.120488501101, 3170.68925311282, -143.026532612836, 258.466914847382, -1451.21045848359, -298.057584698670, -925.765520002125, -4247.87411829111};




this-> A_est_neg=(float[N_state * N_state]){0.59720966405074,	-0.09463059313627,	0.0136065995059,	-0.00058483944842,	-0.00871541727603,	-0.00387574059752,	0.0055734222664,	-0.00448743253752,	0.00332256205251,	-0.01304310959254,
0.05808103891627,	0.26443926221271,	-0.03624365769368,	0.007462754737,	-0.00531118300433,	0.00492179968945,	0.00618657478644,	0.00113695875979,	0.00027893665039,	-0.04126205991101,
-1.38721429050396,	-0.32961591576694,	0.91419703226058,	0.00991285573884,	0.11953379992074,	-0.00407622689792,	-0.04233801255497,	0.02142181449491,	0.00286379011838,	0.04897101470426,
-4.00553100324931,	1.04477035951104,	0.04061621507074,	0.7334805119199,	0.41643459606243,	-0.1124377824652,	0.02131464585836,	-0.0485840731541,	0.4420425652771,	-0.03792210146892,
15.6110689844602,	-9.69824264129979,	-0.71133307677968,	-0.39696831143991,	0.6586421708955,	0.32270810846363,	-0.10599151881485,	0.33912370854014,	0.56035222014213,	0.06003367875984,
-3.97439221235135,	13.9004892033322,	0.91174009549342,	0.16591205546707,	0.01915173938492,	-0.16301458377414,	0.08598731109638,	0.56298279486618,	-0.4577058902986,	-0.35992307815891,
-53.2117404147916,	11.9563144738499,	0.93506525037817,	-0.42890306907793,	0.50012286643259,	-0.32867242539734,	0.31033104640314,	-0.58760734857924,	0.14930478529652,	0.55639227752703,
-44.9567656104768,	8.93957330087458,	0.74165044182528,	-0.20414196195015,	-0.12378836907648,	-0.32565614057489,	-0.52009335950836,	0.31163675823794,	0.77331886782292,	-0.22768903933114,
8.22433240370328,	1.45853345477687,	0.10071748802532,	-0.0666102874654,	0.07482246439538,	0.02073123393099,	0.06699343786698,	0.26240181332522,	-0.12162247494682,	0.21631710250725,
7.54674721514486,	-0.20816986890938,	0.00718009306761,	-0.11280705350897,	-0.03346615423871,	-0.22128706910431,	0.38408950429435,	-0.1143480508164,	0.52994628363548,	-0.15210190528204};


this-> B_est_neg=(float[N_state * ( N_input +  N_output)]) {0.000000196838,	-0.00000021358566,	-0.00000063290488,	0.0000690834671,	-0.00000628608812,	-0.00024821259296,	0.00008097307134,	0.0000453241619,	0.00002118268653,	0.0001279906219,
0.00001387083921,	0.00004418037063,	0.0000380154444,	-0.00002594692613,	-0.00015483520529,	0.00075750853116,	-0.00039508809269,	-0.00059345262617,	0.00050475678692,	0.00026769932043,
-0.12208641291206,	-1.67631069677567,	-0.40486762928366,	3.37528977544983,	-26.3396726680223,	33.6657507274715,	40.0583142222919,	30.919905756605,	1.48874942476968,	-2.22194370708501,
-1.1584007294745,	-1.57974079138161,	-3.86774021833809,	-6.81325796361985,	12.8994011989729,	23.784531356286,	-93.9405125969321,	-82.3735490911895,	22.2950800602933,	16.8079991789524};


this-> C_est_neg=(float[N_state * (N_state +  N_output)]) {0.27492683168771,	-0.09794605152236,	-0.00751172000625,	0.0007549770854,	0.00034348167957,	-0.00106850982211,	-0.00078795438571,	0.0007000697853,	-0.00170584709277,	-0.00085037964373,
-0.04812363355415,	-0.00503157161412,	-0.00017087936169,	-0.0001072005959,	-0.00005566519318,	0.00012382875614,	0.0002046143434,	0.00014755156518,	0.00040170961998,	0.00009014869546,
0.63806183504223,	-0.13199703462776,	-0.00759327271705,	-0.00070031734878,	-0.00039972908614,	0.00066296482417,	0.00182205273518,	0.00225648234353,	0.00345906260441,	0.00042877034969,
-0.60041955056958,	0.43587083895246,	-0.03572117185564,	-0.00077339742322,	-0.00059371879956,	0.00011604683573,	0.00406058715404,	0.00794711247932,	0.00734317076118,	-0.00020239087861,
3.28027828291765,	-1.10547964172633,	0.91460573835082,	0.00893691349864,	0.00408553978702,	-0.01256886851516,	-0.00959138299644,	0.00758360703945,	-0.02064692630042,	-0.00997907867383,
11.3777909018024,	-0.34004774389788,	-0.06208174748927,	1.0270663662232,	0.01346835692564,	-0.0336363294625,	-0.04377656803823,	-0.01625510374975,	-0.08786292120403,	-0.02536288703006,
-21.6320963717449,	4.39795132522216,	0.36936871172046,	-0.05568106565408,	0.97363899903977,	0.0746433297551,	0.07194895128618,	-0.01478509438581,	0.14960643274665,	0.05815185003851,
63.9284983768203,	-22.6441480316111,	-1.73790623288639,	0.17540658958879,	0.07984312841494,	0.75191416485748,	-0.18361679142405,	0.1611891395998,	-0.39726903182255,	-0.1973908395961,
35.794365932722,	1.47365298802192,	-0.02490512995082,	0.08228861959097,	0.04185991370828,	-0.09857029460676,	0.85463077693555,	-0.08211587683951,	-0.28824201709314,	-0.073058485083,
13.6404239262039,	6.70526401750831,	0.40211890103834,	0.02444569427985,	0.014716716063,	-0.02005264378016,	-0.07387257339809,	0.89388105246433,	-0.13840957515633,	-0.01157784558449,
12.979048899084,	-7.96629984641603,	-0.57854984253077,	0.03940247789363,	0.01688742174894,	-0.05996951188054,	-0.02714730042135,	0.07375754453925,	0.93500984466711,	-0.04899328009338,
2.45003502370088,	-1.75835435904737,	-0.12626731040615,	0.00772437519994,	0.00323899192425,	-0.01204590299773,	-0.00435900194522,	0.01702358647102,	-0.01108439430395,	0.99007774098034};

this-> C_inv_neg=(float[N_state *  N_output]) {0.22176116253547,	-2.29864496684191,
-2.34859697878398,	-2.3621682904072,
-0.15811531197131,	-0.15031893052185,
0.00316263521637,	-0.00273307593218,
0.00073334639598,	-0.00223228900467,
-0.00733049642026,	-0.0001327549874,
0.00618966656309,	0.01615438478185,
0.02820695901118,	0.03289051858888,
0.00917722974964,	0.02905397053456,
-0.00669381871653,	-0.00131076219164};



this-> D_est_neg=(float[(N_state + N_output) * (N_input + N_output)]){0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
0.70779300823438,	-0.0011794236461,	-0.2310410542484,	-1.19772468020194,	-3.33742186839304,	-3.33057933225768,	15.1843074749952,	-67.6371428496721,	-4.47636239515182,	12.7910358563791,	-21.6815748848207,	-4.69348614931554,
0.39950580567012,	0.87744963425235,	-1.14511427026955,	-2.71863298037244,	4.91655402131033,	25.3447806490958,	-39.2854327301856,	93.2079652118443,	85.769444995102,	47.2626867745937,	10.9294915974959,	1.45909768338259};


//	this-> N_BAR_neg=(float[N_input +  N_output]) {6692.27395164254, -960.635617013133,
	//						-2256.41280370701, -489.068332481912};


	//more slow
	this-> N_BAR_neg = (float[N_input +  N_output]){-18784.7766284959,	-37599.1016705268,
13086.4535251034,	11823.8193526378};

//  	this-> N_BAR_neg = (float[N_input +  N_output]){-19134.5549568593,	-38544.8904209328,
// 11137.3989456913,	9765.09888343594};
// //
	this-> N_BAR_neg = (float[N_input +  N_output]){-18998.3238497792,	-38065.4469209514,
12497.1806661986,	10773.6945407613};



	this-> K_LQR_neg =(float[N_input * N_state]) {-1043.07071588324,	-186.970458745902,	-208.957238574274,	-219.071918408021,	20.9455793234766,	2.8508107590756,	204.60268069349,	-205.664379308775,	-129.177508644317,	129.71728552684,
2238.03142248889,	401.043101903848,	448.335853669579,	469.988209069038,	-44.9318653122653,	-6.11635798942989,	-438.951070877122,	441.229141489152,	277.137414432251,	-278.290381355991};

 // 	this-> K_LQR_neg =(float[N_input * N_state]) {-826.490910722056,	-239.103324247798,	-168.024833464787,	-223.237208477318,	75.4989508752333,	24.76395794315,	204.429012604416,	-259.127722450775,	-61.2505575975748,	171.217292172828,
 // 2037.24819545459,	359.132355599528,	389.195989589565,	369.149623755115,	-9.46288977328702,	41.7216293689233,	-223.522012588846,	515.337136721435,	167.594235482491,	-243.855689183448};

	this-> K_LQR_neg =(float[N_input * N_state]) {-970.289047353647,	-241.187206917213,	-193.464222924814,	-232.626886392747,	31.8839556535346,	5.70596849683523,	213.778604692893,	-223.748503961239,	-125.167002137461,	143.261776905677,
2352.1521847486,	394.999958341622,	446.095423387083,	443.120546554774,	-33.717312116723,	5.06385567325388,	-389.193911890388,	444.717527046434,	253.67847066363,	-266.59122269614};


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
// Kalman LQR:: KALMAN_FILTER_NEG(float R_real, float Z_real, float I_vertical, float I_horizontal, int sign){
// 	//the same as before
// 	//if we use this in mimo class we can comment from 102 to 115
// 	//i putted because we can copy this in IPID class
// 	float temp=0.0;
// 	int j=0;
// 	int i=0;
// 	int m=0;
// 	int n=0;
// 	// buffers time
//
// 	float buff=0.0;
// 	float buffer=0.0;
//
//
// 	float* y_est;
// 	y_est =(float[2]){0, 0};
// 	float* X_est;
// 	X_est =(float[10]){0, 0,0,0,0,0,0,0,0,0};
//
//
// 	Kalman Outputs={0.085,0.085,X_est};
//
//
// 	buff=0.0;
//
// 	if(sign == 1){
//
// 		for(j = 0; j < N_state; j++){
// 			buff = 0.0;
// 			for (i = 0; i < N_state; i++) {
// 				m=i + j*(N_state);
// 				buff = buff + this->A_est_neg[m] * this->x_neg[i];
// 			}
// 			this->x_dot_neg[j] = buff;
// 		}
//
// 		for(i = 0; i < N_state; i++){
// 			j= i + (N_state);
// 			m=i + 2*(N_state);
// 			n=i + 3*(N_state);
// 			temp =  this->B_est_neg[i] * I_vertical + this->B_est_neg[j] * I_horizontal + this->B_est_neg[m] * R_real + this->B_est_neg[n] * Z_real;
// 			this->x_dot_neg[i] += temp;
//
// 		}
// 		temp = 0.0;
//
// 		//x^(k+1) = A_est * x(k)+ B_est * u(k)
//
// 		//[y_est x_est] = C_est x_est + D_est [u_real y_real]
// 		for(j = 0; j < N_output; j++){
// 			buff = 0.0;
// 			for (i = 0; i < N_state; i++) {
// 				m=i + j*(N_state);
// 				 buff += this->C_est_neg[m] * this->x_neg[i];
// 			}
// 			y_est[j] = buff;
// 		}
//
//
//
// 			buff =  this->D_est_neg[24] * R_real + this->D_est_neg[36] * Z_real;
// 			y_est[0] += buff;
// 			buff = 0.0;
// 			buff =  this->D_est_neg[25] * R_real + this->D_est_neg[37] * Z_real;
// 			y_est[1] += buff;
// 			buff = 0.0;
//
//
//
//
//
//
// 			//x(k)=x(k+1) for the next step
//
//
// 		Outputs.Kalman_R= y_est[0];
// 		Outputs.Kalman_Z= y_est[1];
// 		Outputs.X_est= this-> x_neg;
//
// 		buffer = 0.0;
// 		for (i = 0; i < N_state; i++) {
// 			buffer =this->x_dot_neg[i];
// 			this->x_neg[i]=buffer;
// 		}
//
// 			for(i=0; i< N_state; i++){
// 		buff = this->x_neg[i];
// 		this->X_LQR_neg[i] = buff;
// 	}
//
// 		}else{
// 			Outputs.Kalman_R= 0.085;
// 			Outputs.Kalman_Z= 0.085;
// 				for (i = 0; i < N_state; i++) {
// 						X_est[i]=0.0;}
//
// 			Outputs.X_est=X_est;
// 			}
//
//
// 	return Outputs;
//
// }




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
//
// Kalman LQR:: KALMAN_FILTER_NEG(float R_real, float Z_real, float I_vertical, float I_horizontal, int sign){
// 	//the same as before
// 	//if we use this in mimo class we can comment from 102 to 115
// 	//i putted because we can copy this in IPID class
// 	float temp=0.0;
// 	int j=0;
// 	int i=0;
// 	int m=0;
// 	int n=0;
// 	// buffers time
//
// 	float buff=0.0;
// 	float buffer=0.0;
//
//
// 	float* y_est;
// 	y_est =(float[2]){0, 0};
// 	float* X_est;
// 	X_est =(float[10]){0, 0,0,0,0,0,0,0,0,0};
// 	Kalman Outputs={0.085,0.085,X_est};
//
//
// 	buff=0.0;
// 	if(sign == 1){
//
//
// 		// Lets do Ax + Bu
// 				for(j = 0; j < N_state; j++){
// 					buff = 0.0;
// 					for (i = 0; i < N_state; i++) {
// 						m=i + j*(N_state);
// 						buff = buff + this->A_est_neg[m] * this->x_neg[i];
// 					}
// 					this->x_dot_neg[j] = buff;
// 				}
//
// 				for(i = 0; i < N_state; i++){
// 					j= i + (N_state);
// 					m=i + 2*(N_state);
// 					n=i + 3*(N_state);
// 					temp =  this->B_est_neg[i] * I_vertical + this->B_est_neg[j] * I_horizontal + this->B_est_neg[m] * R_real + this->B_est_neg[n] * Z_real;
// 					this->x_dot_neg[i] += temp;
//
// 				}
// 				temp = 0.0;
//
//
//
// 		//[y_est x_est] = C_est x_est + D_est [u_real y_real]
// 		for(j = 0; j < N_output; j++){
// 			buff = 0.0;
// 			for (i = 0; i < N_state; i++) {
// 				m=i + j*(N_state);
// 				 buff += this->C_est_neg[m] * this->x_neg[i];
// 			}
// 			y_est[j] = buff;
// 		}
//
//
//
// 			buff =  this->D_est_neg[24] * R_real + this->D_est_neg[36] * Z_real;
// 			y_est[0] += buff;
// 			buff = 0.0;
// 			buff =  this->D_est_neg[25] * R_real + this->D_est_neg[37] * Z_real;
// 			y_est[1] += buff;
// 			buff = 0.0;
//
// // Lets take the states from y_est
// 		for(j = N_output; j < N_state+N_output; j++){
// 			buff = 0.0;
// 			for (i = 0; i < N_state; i++) {
// 				m=i + j*(N_state);
// 				 buff += this->C_est_neg[m] * this->x_neg[i];
// 			}
// 			 this->x_neg[j-N_output] = buff;
// 		}
//
// 		buff =  this->D_est_neg[26] * R_real + this->D_est_neg[38] * Z_real;
// 		x_neg[0] += buff;
// 		buff = 0.0;
// 		buff =  this->D_est_neg[27] * R_real + this->D_est_neg[39] * Z_real;
// 		x_neg[1]  += buff;
// 		buff = 0.0;
// 		buff =  this->D_est_neg[28] * R_real + this->D_est_neg[40] * Z_real;
// 		x_neg[2] += buff;
// 		buff = 0.0;
// 		buff =  this->D_est_neg[29] * R_real + this->D_est_neg[41] * Z_real;
// 		x_neg[3]  += buff;
// 		buff = 0.0;
// 		buff =  this->D_est_neg[30] * R_real + this->D_est_neg[42] * Z_real;
// 		x_neg[4]  += buff;
// 		buff = 0.0;
// 		buff =  this->D_est_neg[31] * R_real + this->D_est_neg[43] * Z_real;
// 		x_neg[5] += buff;
// 		buff = 0.0;
// 		buff =  this->D_est_neg[32] * R_real + this->D_est_neg[44] * Z_real;
// 		x_neg[6]  += buff;
// 		buff = 0.0;
// 		buff =  this->D_est_neg[33] * R_real + this->D_est_neg[45] * Z_real;
// 		x_neg[7]  += buff;
// 		buff = 0.0;
// 		buff =  this->D_est_neg[34] * R_real + this->D_est_neg[46] * Z_real;
// 		x_neg[8] += buff;
// 		buff = 0.0;
// 		buff =  this->D_est_neg[35] * R_real + this->D_est_neg[47] * Z_real;
// 		x_neg[9]  += buff;
// 		buff = 0.0;
//
//
//
//
//
//
//
//
//
//
//
// 			//x(k)=x(k+1) for the next step
//
//
// 		Outputs.Kalman_R= y_est[0];
// 		Outputs.Kalman_Z= y_est[1];
// 		Outputs.X_est=this->x_neg;
//
// 		buffer = 0.0;
// 		for (i = 0; i < N_state; i++) {
// 			buffer =this->x_dot_neg[i];
// 			this->x_neg[i]=buffer;
// 		}
//
// 				for(i=0; i< N_state; i++){
// 				buff = this->x_neg[i];
// 				this->X_LQR_neg[i] = buff;
// 				}
//
// 		}else{
// 			Outputs.Kalman_R= 0.085;
// 			Outputs.Kalman_Z= 0.085;
// 				for (i = 0; i < N_state; i++) {
// 						X_est[i]=0.0;}
//
// 			Outputs.X_est=X_est;
// 			}
//
//
// 	return Outputs;
//
// }

int LQR:: erase(float R_real, float Z_real) {
	int j = 0;
	int i = 0;
	float* state0_pos;
	float* state0_neg;
	float tempR=0;
	float tempz=0;
	float temp=0;
	state0_pos = (float[N_state]){-0.005344092,	0.0520246,	-0.514431535,	1.150989527,	0.550062681,	-0.87777012,	0.308169602,	-0.356773408,	1.066604321,	-0.186231247};
	state0_pos = (float[N_state]){0.0191923,	0.289779,	0.309377,	0.0539503,	-0.2685851,	0.6644621,	-1.0757866,	-0.0274285,	0.1494512,	-0.3546514};
	state0_pos = (float[N_state]){	0.0075 ,   0.2071 ,  -0.0394  , -0.1344  , -0.0625   , 0.4041  , -0.5053 ,   0.0973  ,  0.2590,   -0.0032};
	state0_pos = (float[N_state]){-0.00794,	0.08333,	-0.32369,	-0.20072,	0.35133,	-0.03818,	0.82502,	0.03578,	-0.12314,	0.00307};
//state0_pos = (float[N_state]){-0.00338,	0.14165,	-0.1744,	-0.54187,	-0.27558,	0.13963,	1.61163,	0.23229,	-0.83422,	-0.13946};
//state0_pos = (float[N_state]){-0.00566913759758476,	0.121490081315979,	0.0409696382595862,	-0.326033663487195,	-0.132618254130713,	0.145414194373366,	0.640709770994902	,0.220661833695255	,-0.375976754083591,	-0.0476667263059292};

		state0_neg=(float[N_state])  {0,0,0,0,0,0,0,0,0,0};
	state0_neg=(float[N_state])  {0.032456363499452,	-0.063785306076201,	0.124571869100746,	-0.065387443522556,	0.093090988857802,	-1.40440635057351,	-0.320533077979534,	0.246014136258589,	-0.076864950567127,	0.599032477284996};
	state0_neg=(float[N_state])  {0.054207867846701,	-0.052337115646198,	0.038441642608233,	-0.034164545243869,	0.218126249484017,	0.24417046356667,	-0.322416522481022,	-0.066889754294555,	-0.389451884260603,	0.278935578024248};
	state0_neg=(float[N_state])  {0.016810611810391,	-0.078703906791538,	0.209254630418628,	0.03556454476693,	0.083981660502173,	-0.683348686404463,	-0.213786377122719,	0.177045937944626,	-0.252841577523042,	0.709383785099129};
	state0_neg=(float[N_state])   {0.0555035358095847,	-0.0129555570766988,	0.00523003615303577	,-0.0290025216580580	,0.0624195965501496	-0.169313794694064,	0.144650598039852	,0.00366822605174714,	-0.0505172707740238,	-0.098042187340031};
state0_neg=(float[N_state])   {	0.011489721761823,	-0.103275605316704,	0.230889418040253,	0.080085093022331,	-0.075841805411825,	-0.830726272789686,	-0.13293929661096,	0.338417479411358,	-0.251475684125608,	0.935264122858397};
state0_neg=(float[N_state])   {-0.009741366241305,	-0.205912818018256,	0.198602091754336,	0.070552052210391,	0.219878908860687,	-0.289459715701652,	-0.249161976447696,	0.085702144441041,	-0.306982640761359,	0.246668394499494};
state0_neg=(float[N_state])   {0.048686371278709,	-0.060937894056835,	-0.044287248204942,	-0.069077880371761,	0.099010490176201,	0.188131610082302,	-0.054100669322058,	-0.139779569622899,	-0.224157306520685,	-0.095990081022785};

	// for(j = 0; j < N_state; j++){
	// 			tempR =  this->C_inv_neg[2*j] * R_real;
	// 			tempz =  this->C_inv_neg[2*j+1] * Z_real;
	// 		state0_neg[j] = tempR+tempz;
	// 	}


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
