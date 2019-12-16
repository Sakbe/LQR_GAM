
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

	this-> X_LQR_neg = (float[N_state]){0.032456363499452,	-0.063785306076201,	0.124571869100746,	-0.065387443522556,	0.093090988857802,	-1.40440635057351,	-0.320533077979534,	0.246014136258589,	-0.076864950567127,	0.599032477284996};
	this-> X_LQR_neg = (float[N_state]){0.054207867846701,	-0.052337115646198,	0.038441642608233,	-0.034164545243869,	0.218126249484017,	0.24417046356667,	-0.322416522481022,	-0.066889754294555,	-0.389451884260603,	0.278935578024248};

	this-> x_dot_pos = (float[N_state]){0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

	this-> x_pos = (float[N_state]){-0.005344092,	0.0520246,	-0.514431535,	1.150989527,	0.550062681,	-0.87777012,	0.308169602,	-0.356773408,	1.066604321,	-0.186231247};
	this-> x_pos = (float[N_state]){-0.00338,	0.14165,	-0.1744,	-0.54187,	-0.27558,	0.13963,	1.61163,	0.23229,	-0.83422,	-0.13946};

	this-> x_pos = (float[N_state]){-0.00794,	0.08333,	-0.32369,	-0.20072,	0.35133,	-0.03818,	0.82502,	0.03578,	-0.12314,	0.00307};

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


	this-> x_dot_neg=(float[N_state])  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
//	this-> K_LQR_neg=(float[N_input * N_state])  {-1.10243700688381, -26.6888168111469, 248.208386299799, 2272.69314089294, 341.435985384170, 116.974185358079, -1571.00753489878, -331.351679250269, -1271.06969797964, -4441.09340489016,
//							-0.233414809301534, -21.1374545809135, 237.120488501101, 3170.68925311282, -143.026532612836, 258.466914847382, -1451.21045848359, -298.057584698670, -925.765520002125, -4247.87411829111};


this-> A_est_neg=(float[N_state * N_state]){0.32699420554739,	-0.040081077706528,	0.018194601328953,	-0.001279939093956,	-0.009044625610037,	-0.002944443226786,	0.006473330507918,	-0.004667404462931,	0.00519315785646,	-0.012317735528208,
-0.187147784038141,	0.376595753479117,	-0.027882457075559,	0.006761437855813,	-0.00562254530058,	0.005945544080379,	0.006814861099911,	0.000210575449892,	0.001685243149724,	-0.040437915494302,
0.622273593431543,	-0.823669281862743,	0.87415597667641,	0.015181495702834,	0.121999765222301,	-0.011253846914439,	-0.048764471632389,	0.023836729873426,	-0.010636111166242,	0.04334270991015,
1.22691768387672,	-0.800410714152554,	-0.101078848181408,	0.747828035244837,	0.422967982546704,	-0.132719832125345,	0.006261213769654,	-0.03549095278957,	0.40948854665148,	-0.0540565102885,
13.1050113163842,	-8.31602280220657,	-0.610072207179985,	-0.404400861782636,	0.655412818842341,	0.333842830224819,	-0.100280798928748,	0.326781645664034,	0.573625983120709,	0.069080714915086,
15.630420580863,	10.3933872521281,	0.609058113846384,	0.215836286379233,	0.042946043060615,	-0.229298282218181,	0.019341620594735,	0.570552138021459,	-0.595517555509122,	-0.411357994460248,
-25.3041680620609,	5.05364123736974,	0.376211436387723,	-0.355686231224983,	0.534378257525137,	-0.428472247558954,	0.221205231705985,	-0.553566130386418,	-0.037988455744586,	0.478117580134131,
-24.3731275166287,	4.31499438096057,	0.360719756321102,	-0.150664799928838,	-0.098616609250278,	-0.397935123668611,	-0.587232559384948,	0.331061585980887,	0.63300844476211,	-0.284186569923459,
7.30790140675962,	1.45010209359046,	0.103318013603451,	-0.068750060107029,	0.073744849038808,	0.023338398838412,	0.070627169888138,	0.264147365218676,	-0.114378943294644,	0.218265149674442,
3.42640217433352,	0.062785130531758,	0.039565207063651,	-0.122775158430582,	-0.038373291730924,	-0.208684755156136,	0.399498215578452,	-0.11026168078121,	0.561077607098738,	-0.142525735519462};


this-> B_est_neg=(float[N_state * ( N_input +  N_output)]) {0.000000196837997,	-0.000000213585657,	-0.000000632904875,	0.000069083467104,	-0.000006286088122,	-0.000248212592964,	0.000080973071337,	0.000045324161898,	0.000021182686533,	0.000127990621898,
0.000013870839215,	0.000044180370632,	0.000038015444404,	-0.000025946926127,	-0.000154835205292,	0.000757508531156,	-0.000395088092687,	-0.000593452626168,	0.000504756786919,	0.00026769932043,
0.066673603378913,	-1.35717123437739,	-2.01717055513955,	-2.14133921355515,	-22.5212791488976,	21.0339951540631,	17.5693357547733,	15.4338108915673,	1.67248904695787,	-0.667031257002857,
-1.65004986054401,	-1.87726737180009,	-0.421268944298726,	0.835144521939658,	10.4190354958289,	60.5241167377655,	-46.1742715390805,	-46.0357267895517,	20.1686732555583,	7.98038641047657};


this-> C_est_neg=(float[N_state * (N_state +  N_output)]) {0.303753710101153,	-0.103315165799794,	-0.00797100505277,	0.000828624424383,	0.000378511454468,	-0.001166578262399,	-0.000885311703043,	0.000713785156749,	-0.001907498039054,	-0.000926571371008,
-0.057952492616352,	-0.000995272087076,	0.000133490676976,	-0.000134793209345,	-0.00006805243185,	0.000163552668976,	0.000231176532989,	0.000116011804333,	0.000460209030105,	0.000121965741854,
0.44446874135458,	-0.098853321288095,	-0.004704056770899,	-0.00119163346027,	-0.000634393276494,	0.001313260018707,	0.002484639035687,	0.002199861268373,	0.004826841157766,	0.000932739269081,
-0.427014534017915,	0.39510706545787,	-0.039051179496727,	-0.00032085359299,	-0.000381298794075,	-0.000498003813135,	0.003500405336056,	0.008132731985525,	0.006169528404982,	-0.000683125793729,
2.36904813005218,	-0.971433566725839,	0.9267338840756,	0.006649028063979,	0.002985405413013,	-0.009570557683982,	-0.006406595132343,	0.007584545661574,	-0.014106774697929,	-0.007665058391426,
6.8679967707745,	-0.130819152511117,	-0.032486949280145,	1.01625435819487,	0.008114962359693,	-0.020091783223865,	-0.026648803677487,	-0.010718787371366,	-0.053383009756959,	-0.015112782326411,
0.709422848580278,	0.286402853918043,	0.016737793569658,	0.001341524185627,	1.00077793069025,	-0.001220563984448,	-0.003654584965352,	-0.004759979869346,	-0.00690869910051,	-0.000767146307163,
28.4738446823775,	-13.4385911555962,	-0.9986977138272,	0.081898848351371,	0.036236314775892,	0.879946163675186,	-0.071700285243719,	0.112629642051846,	-0.161354015421071,	-0.096793579227483,
31.973434626959,	2.13258369788815,	0.03243906487049,	0.072586179383986,	0.037227405306673,	-0.085721858775945,	0.867693827029155,	-0.083291570138271,	-0.261268489013657,	-0.06309904868023,
22.1436545381511,	5.15364877727667,	0.268794456107735,	0.046133708220648,	0.02504318860456,	-0.048888844752621,	-0.102687286257743,	0.897535267703996,	-0.198041178943148,	-0.033967471467821,
1.72844354300019,	-6.26839296656531,	-0.425934689772967,	0.011106583212846,	0.003295866055499,	-0.022828283285634,	0.012045053227424,	0.073246734835351,	1.0155591204479,	-0.020309428681518,
-3.90633138876809,	-2.12651289857256,	-0.128977650636143,	-0.006768651892345,	-0.004173090389665,	0.005154773523148,	0.021775850477458,	0.032902436344112,	0.040596699694902,	1.00276964124178};




this-> D_est_neg=(float[(N_state + N_output) * (N_input + N_output)]){0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
0.68871839942088,	0.0105287908944,	-0.109816760528488,	-1.33244368262672,	-2.81864280650608,	-1.83478170155578,	0.518170335464437,	-38.0372028051623,	-2.07249885801287,	7.24033516109032,	-15.1752014744304,	-4.14979715492256,
0.453023920908802,	0.864435600707929,	-1.51144042866616,	-2.41678982557099,	3.14017512036199,	15.4755600448006,	2.3101795636772,	33.5592264140918,	78.5506274839976,	63.1255044960994,	-10.9009947905673,	-14.0244750553621};

//	this-> N_BAR_neg=(float[N_input +  N_output]) {6692.27395164254, -960.635617013133,
	//						-2256.41280370701, -489.068332481912};


	//more slow
	this-> N_BAR_neg = (float[N_input +  N_output]){-18784.7766284959,	-37599.1016705268,
13086.4535251034,	11823.8193526378};

	this-> N_BAR_neg = (float[N_input +  N_output]){-19134.5549568593,	-38544.8904209328,
11137.3989456913,	9765.09888343594};



	this-> K_LQR_neg =(float[N_input * N_state]) {-1043.07071588324,	-186.970458745902,	-208.957238574274,	-219.071918408021,	20.9455793234766,	2.8508107590756,	204.60268069349,	-205.664379308775,	-129.177508644317,	129.71728552684,
2238.03142248889,	401.043101903848,	448.335853669579,	469.988209069038,	-44.9318653122653,	-6.11635798942989,	-438.951070877122,	441.229141489152,	277.137414432251,	-278.290381355991};

	this-> K_LQR_neg =(float[N_input * N_state]) {-826.490910722056,	-239.103324247798,	-168.024833464787,	-223.237208477318,	75.4989508752333,	24.76395794315,	204.429012604416,	-259.127722450775,	-61.2505575975748,	171.217292172828,
2037.24819545459,	359.132355599528,	389.195989589565,	369.149623755115,	-9.46288977328702,	41.7216293689233,	-223.522012588846,	515.337136721435,	167.594235482491,	-243.855689183448};


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
	int i = 0;
	float* state0_pos;
	float* state0_neg;
	state0_pos = (float[N_state]){-0.005344092,	0.0520246,	-0.514431535,	1.150989527,	0.550062681,	-0.87777012,	0.308169602,	-0.356773408,	1.066604321,	-0.186231247};
	state0_pos = (float[N_state]){0.0191923,	0.289779,	0.309377,	0.0539503,	-0.2685851,	0.6644621,	-1.0757866,	-0.0274285,	0.1494512,	-0.3546514};
	state0_pos = (float[N_state]){	0.0075 ,   0.2071 ,  -0.0394  , -0.1344  , -0.0625   , 0.4041  , -0.5053 ,   0.0973  ,  0.2590,   -0.0032};
	state0_pos = (float[N_state]){-0.00794,	0.08333,	-0.32369,	-0.20072,	0.35133,	-0.03818,	0.82502,	0.03578,	-0.12314,	0.00307};
//state0_pos = (float[N_state]){-0.00338,	0.14165,	-0.1744,	-0.54187,	-0.27558,	0.13963,	1.61163,	0.23229,	-0.83422,	-0.13946};


		state0_neg=(float[N_state])  {0,0,0,0,0,0,0,0,0,0};
	state0_neg=(float[N_state])  {0.032456363499452,	-0.063785306076201,	0.124571869100746,	-0.065387443522556,	0.093090988857802,	-1.40440635057351,	-0.320533077979534,	0.246014136258589,	-0.076864950567127,	0.599032477284996};
	state0_neg=(float[N_state])  {0.054207867846701,	-0.052337115646198,	0.038441642608233,	-0.034164545243869,	0.218126249484017,	0.24417046356667,	-0.322416522481022,	-0.066889754294555,	-0.389451884260603,	0.278935578024248};



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
