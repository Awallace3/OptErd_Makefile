#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "erd.h"

#ifdef __INTEL_OFFLOAD
#pragma offload_attribute(push, target(mic))
#endif


/* ------------------------------------------------------------------------ */
/*  OPERATION   : ERD__RYS_5_ROOTS_WEIGHTS */
/*  MODULE      : ELECTRON REPULSION INTEGRALS DIRECT */
/*  MODULE-ID   : ERD */
/*  SUBROUTINES : none */
/*  DESCRIPTION : This operation returns Rys polynomial roots and weights */
/*                in case the number of roots and weights required */
/*                is = 5. All T's are treated at once so the complete */
/*                set of roots and weights is returned. */
/*                For the moment taken essentially unchanged from the */
/*                GAMESS package (routine ROOT5, but removing their */
/*                'spaghetti' code from the 70's of unreadable */
/*                internested IFs and GOTOs!). */
/*                One interesting aspect of the GAMESS routines is that */
/*                their code returns scaled roots, i.e. their roots */
/*                do not ly between the range 0 and 1. To get to the */
/*                proper roots as needed for our package, we simply */
/*                set: */
/*                   root (our) = root (gamess) / (1 + root (games)) */
/*                  Input: */
/*                    NT           =  # of T-exponents */
/*                    NTGQP        =  # of roots times # of T-exponents */
/*                                    (= 5 * NT) */
/*                    TVAL         =  the set of NT T-exponents defining */
/*                                    the Rys weight functions */
/*                  Output: */
/*                    RTS          =  all NTGQP quadrature roots */
/*                    WTS          =  all NTGQP quadrature weights */
/* ------------------------------------------------------------------------ */
void erd__rys_5_roots_weights(int nt, const double tval[restrict], double rts[restrict], double wts[restrict]) {
    int jump5[60] =
        { 1, 2, 2, 2, 2, 3, 3, 3, 3, 3, 4, 4, 4, 4, 4, 5, 5, 5, 5, 5, 6, 6,
        6, 6, 6, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 8, 8, 8, 8, 8,
            8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
        8, 8, 8, 8, 9
    };

    double e;
    int m, n;
    double t, x, r1, r2, r3, r4, r5, w1, w2, w3, w4, w5;
    int tcase;

/* ------------------------------------------------------------------------ */
/*                 ******************************** */
/*             ... *  # of roots and weights = 5  * */
/*                 ******************************** */
    m = 0;
    for (n = 0; n < nt; ++n)
    {
        t = tval[n];
        if (t <= 3e-7)
        {
/*             ...T-range: T essentially 0 */
            r1 = .0226659266316985 - t * .00215865967920897;
            r2 = .231271692140903 - t * .0220258754389745;
            r3 = .857346024118836 - t * .0816520023025515;
            r4 = 2.97353038120346 - t * .283193369647137;
            r5 = 18.4151859759051 - t * 1.75382723579439;
            wts[m] *= .295524224714752 - t * .0196867576909777;
            wts[m + 1] *= .269266719309995 - t * .0561737590184721;
            wts[m + 2] *= .219086362515981 - t * .0971152726793658;
            wts[m + 3] *= .14945134915058 - t * .102979262193565;
            wts[m + 4] *= .0666713443086877 - t * .0573782817488315;
            rts[m] = r1 / (r1 + 1.);
            rts[m + 1] = r2 / (r2 + 1.);
            rts[m + 2] = r3 / (r3 + 1.);
            rts[m + 3] = r4 / (r4 + 1.);
            rts[m + 4] = r5 / (r5 + 1.);
            m += 5;
            goto L500;
        }

        tcase = (int) MIN ((t + 1.0), 60.);
        switch (jump5[tcase - 1])
        {
        case 1:
            goto L5100;
        case 2:
            goto L5200;
        case 3:
            goto L5300;
        case 4:
            goto L5400;
        case 5:
            goto L5500;
        case 6:
            goto L5600;
        case 7:
            goto L5700;
        case 8:
            goto L5800;
        case 9:
            goto L5900;
        }


/*             ...T-range: 0 < T < 1 */
      L5100:
        wts[m] *= ((((((t * -2.03822632771791e-9 + 3.8911022913381e-8) * t -
                      5.84914787904823e-7) * t + 8.30316168666696e-6) * t -
                    1.13218402310546e-4) * t + .0014912888858679) * t -
                  .0196867576904816) * t + .295524224714749;
        wts[m + 1] *= (((((((t * 8.6284811839757e-9 - 1.38975551148989e-7) * t
                           + 1.602894068228e-6) * t - 1.646364300836e-5) * t +
                         1.538445806778e-4) * t - .00128848868034502) * t +
                       .00938866933338584) * t - .0561737590178812) * t +
            .269266719309991;
        wts[m + 2] *= ((((((((t * -9.41953204205665e-9 + 1.47452251067755e-7) *
                            t - 1.57456991199322e-6) * t +
                           1.45098401798393e-5) * t -
                          1.18858834181513e-4) * t + 8.5369767598421e-4) * t -
                        .00522877807397165) * t + .0260854524809786) * t -
                      .0971152726809059) * t + .219086362515979;
        wts[m + 3] *=
            ((((((((t * -3.84961617022042e-8 + 5.6659539654447e-7) * t -
                   5.52351805403748e-6) * t + 4.53160377546073e-5) * t -
                 3.22542784865557e-4) * t + .00195682017370967) * t -
               .00977232537679229) * t + .0379455945268632) * t -
             .102979262192227) * t + .149451349150573;
        wts[m + 4] *=
            (((((((((t * 4.0959481252143e-9 - 6.47097874264417e-8) * t +
                    6.743541482689e-7) * t - 5.917993920224e-6) * t +
                  4.531969237381e-5) * t - 2.99102856679638e-4) * t +
                .00165695765202643) * t - .00740671222520653) * t +
              .0250889946832192) * t - .0573782817487958) * t +
            .0666713443086877;
        r1 = ((((((t * -4.46679165328413e-11 + 1.21879111988031e-9) * t -
                  2.62975022612104e-8) * t + 5.15106194905897e-7) * t -
                9.27933625824749e-6) * t + 1.51794097682482e-4) * t -
              .00215865967920301) * t + .0226659266316985;
        r2 = ((((((t * 1.93117331714174e-10 - 4.57267589660699e-9) * t +
                  2.48339908218932e-8) * t + 1.50716729438474e-6) * t -
                6.07268757707381e-5) * t + .00137506939145643) * t -
              .0220258754419939) * t + .231271692140905;
        r3 = (((((t * 4.84989776180094e-9 + 1.31538893944284e-7) * t -
                 2.766753852879e-6) * t - 7.651163510626e-5) * t +
               .004033058545972) * t - .0816520022916145) * t +
            .857346024118779;
        r4 = ((((t * -2.48581772214623e-7 - 4.34482635782585e-6) * t -
                7.4601825798763e-7) * t + .0101210776517279) * t -
              .283193369640005) * t + 2.97353038120345;
        r5 = (((((t * -8.92432153868554e-9 + 1.77288899268988e-8) * t +
                 3.040754680666e-6) * t + 1.058229325071e-4) * t +
               .04596379534985) * t - 1.75382723579114) * t +
            18.4151859759049;
        rts[m] = r1 / (r1 + 1.);
        rts[m + 1] = r2 / (r2 + 1.);
        rts[m + 2] = r3 / (r3 + 1.);
        rts[m + 3] = r4 / (r4 + 1.);
        rts[m + 4] = r5 / (r5 + 1.);
        m += 5;
        goto L500;


/*             ...T-range: 1 =< T < 5 */
      L5200:
        x = t - 3.;
        wts[m] *= (((((((((x * 1.04348658616398e-13 - 1.94147461891055e-12) *
                         x + 3.485512360993e-11) * x -
                        6.277497362235e-10) * x + 1.100758247388e-8) * x -
                      1.88329804969573e-7) * x + 3.12338120839468e-6) * x -
                    5.04404167403568e-5) * x + 8.00338056610995e-4) * x -
                  .0130892406559521) * x + .247383140241103;
        wts[m + 1] *=
            (((((((((((x * 3.23496149760478e-14 - 5.24314473469311e-13) * x +
                      7.743219385056e-12) * x - 1.146022750992e-10) * x +
                    1.615238462197e-9) * x - 2.15479017572233e-8) * x +
                  2.70933462557631e-7) * x - 3.18750295288531e-6) * x +
                3.47425221210099e-5) * x - 3.45558237388223e-4) * x +
              .00305779768191621) * x - .0229118251223003) * x +
            .159834227924213;
        wts[m + 2] *=
            ((((((((((((x * -3.42790561802876e-14 +
                        5.26475736681542e-13) * x - 7.184330797139e-12) * x +
                      9.763932908544e-11) * x - 1.244014559219e-9) * x +
                    1.472744068942e-8) * x - 1.611749975234e-7) * x +
                  1.616487851917e-6) * x - 1.46852359124154e-5) * x +
                1.18900349101069e-4) * x - 8.37562373221756e-4) * x +
              .00493752683045845) * x - .0225514728915673) * x +
            .0695211812453929;
        wts[m + 3] *=
            (((((((((((((x * 1.04072340345039e-14 -
                         1.60808044529211e-13) * x + 2.183534866798e-12) * x -
                       2.939403008391e-11) * x + 3.679254029085e-10) * x -
                     4.23775673047899e-9) * x + 4.46559231067006e-8) * x -
                   4.26488836563267e-7) * x + 3.64721335274973e-6) * x -
                 2.74868382777722e-5) * x + 1.78586118867488e-4) * x -
               9.68428981886534e-4) * x + .00416002324339929) * x -
             .0128290192663141) * x + .0222353727685016;
        wts[m + 4] *=
            ((((((((((((((x * -8.16770412525963e-16 +
                          1.31376515047977e-14) * x -
                         1.856950818865e-13) * x + 2.596836515749e-12) * x -
                       3.372639523006e-11) * x + 4.025371849467e-10) * x -
                     4.389453269417e-9) * x + 4.332753856271e-8) * x -
                   3.82673275931962e-7) * x + 2.98006900751543e-6) * x -
                 2.00718990300052e-5) * x + 1.13876001386361e-4) * x -
               5.23627942443563e-4) * x + .00183524565118203) * x -
             .00437785737450783) * x + .00536963805223095;
        r1 = ((((((((x * -2.58163897135138e-14 + 8.14127461488273e-13) * x -
                    2.11414838976129e-11) * x + 5.09822003260014e-10) * x -
                  1.16002134438663e-8) * x + 2.4681069441454e-7) * x -
                4.92556826124502e-6) * x + 9.02580687971053e-5) * x -
              .00145190025120726) * x + .0173416786387475;
        r2 = (((((((((x * 1.04525287289788e-14 + 5.44611782010773e-14) * x -
                     4.831059411392e-12) * x + 1.136643908832e-10) * x -
                   1.104373076913e-9) * x - 2.35346740649916e-8) * x +
                 1.43772622028764e-6) * x - 4.23405023015273e-5) * x +
               9.12034574793379e-4) * x - .0152479441718739) * x +
            .176055265928744;
        r3 = (((((((((x * -6.89693150857911e-14 + 5.92064260918861e-13) * x +
                     1.847170956043e-11) * x - 3.390752744265e-10) * x -
                   2.995532064116e-9) * x + 1.57456141058535e-7) * x -
                 3.95859409711346e-7) * x - 9.58924580919747e-5) * x +
               .00323551502557785) * x - .0597587007636479) * x +
            .646432853383057;
        r4 = ((((((((x * -3.61293809667763e-12 - 2.70803518291085e-11) * x +
                    8.83758848468769e-10) * x + 1.59166632851267e-8) * x -
                  1.32581997983422e-7) * x - 7.60223407443995e-6) * x -
                7.41019244900952e-5) * x + .00981432631743423) * x -
              .223055570487771) * x + 2.21460798080643;
        r5 = (((((((((x * 7.12332088345321e-13 + 3.16578501501894e-12) * x -
                     8.776668218053e-11) * x - 2.342817613343e-9) * x -
                   3.496962018025e-8) * x - 3.03172870136802e-7) * x +
                 1.50511293969805e-6) * x + 1.37704919387696e-4) * x +
               .0470723869619745) * x - 1.47486623003693) * x +
            13.5704792175847;
        rts[m] = r1 / (r1 + 1.);
        rts[m + 1] = r2 / (r2 + 1.);
        rts[m + 2] = r3 / (r3 + 1.);
        rts[m + 3] = r4 / (r4 + 1.);
        rts[m + 4] = r5 / (r5 + 1.);
        m += 5;
        goto L500;


/*             ...T-range: 5 =< T < 10 */
      L5300:
        x = t - 7.5;
        wts[m] *= (((((((((x * 7.95526040108997e-15 - 2.48593096128045e-13) *
                         x + 4.76124620872e-12) * x -
                        9.535763686605e-11) * x + 2.225273630974e-9) * x -
                      4.49796778054865e-8) * x + 9.17812870287386e-7) * x -
                    1.86764236490502e-5) * x + 3.76807779068053e-4) * x -
                  .00810456360143408) * x + .201097936411496;
        wts[m + 1] *=
            (((((((((((x * 1.25678686624734e-15 - 2.34266248891173e-14) * x +
                      3.973252415832e-13) * x - 6.830539401049e-12) * x +
                    1.140771033372e-10) * x - 1.82546185762009e-9) * x +
                  2.77209637550134e-8) * x - 4.01726946190383e-7) * x +
                5.48227244014763e-6) * x - 6.95676245982121e-5) * x +
              8.05193921815776e-4) * x - .00815528438784469) * x +
            .0971769901268114;
        wts[m + 2] *=
            ((((((((((((x * -8.20929494859896e-16 +
                        1.37356038393016e-14) * x - 2.02286306522e-13) * x +
                      3.058055403795e-12) * x - 4.387890955243e-11) * x +
                    5.923946274445e-10) * x - 7.503659964159e-9) * x +
                  8.851599803902e-8) * x - 9.65561998415038e-7) * x +
                9.60884622778092e-6) * x - 8.56551787594404e-5) * x +
              6.66057194311179e-4) * x - .00417753183902198) * x +
            .0225443826852447;
        wts[m + 3] *=
            ((((((((((((((x * -1.0876461248879e-17 +
                          1.85299909689937e-16) * x -
                         2.730195628655e-15) * x + 4.127368817265e-14) * x -
                       5.881379088074e-13) * x + 7.805245193391e-12) * x -
                     9.632707991704e-11) * x + 1.099047050624e-9) * x -
                   1.15042731790748e-8) * x + 1.09415155268932e-7) * x -
                 9.33687124875935e-7) * x + 7.02338477986218e-6) * x -
               4.53759748787756e-5) * x + 2.41722511389146e-4) * x -
             9.75935943447037e-4) * x + .00257520532789644;
        wts[m + 4] *=
            (((((((((((((((x * 7.28996979748849e-19 -
                           1.26518146195173e-17) * x +
                          1.886145834486e-16) * x - 2.876728287383e-15) * x +
                        4.114588668138e-14) * x - 5.44436631413933e-13) * x +
                      6.64976446790959e-12) * x - 7.4456006997494e-11) * x +
                    7.57553198166848e-10) * x - 6.92956101109829e-9) * x +
                  5.62222859033624e-8) * x - 3.97500114084351e-7) * x +
                2.3903912613814e-6) * x - 1.18023950002105e-5) * x +
              4.52254031046244e-5) * x - 1.2111378215037e-4) * x +
            1.75013126731224e-4;
        r1 = ((((((((x * -1.13825201010775e-14 + 1.89737681670375e-13) * x -
                    4.81561201185876e-12) * x + 1.56666512163407e-10) * x -
                  3.73782213255083e-9) * x + 9.15858355075147e-8) * x -
                2.13775073585629e-6) * x + 4.56547356365536e-5) * x -
              8.6800390932374e-4) * x + .0122703754069176;
        r2 = (((((((((x * -3.67160504428358e-15 + 1.27876280158297e-14) * x -
                     1.296476623788e-12) * x + 1.477175434354e-11) * x +
                   5.464102147892e-10) * x - 2.42538340602723e-8) * x +
                 8.20460740637617e-7) * x - 2.20379304598661e-5) * x +
               4.90295372978785e-4) * x - .00914294111576119) * x +
            .12259040340369;
        r3 = (((((((((x * 1.39017367502123e-14 - 6.9639138542689e-13) * x +
                     1.176946020731e-12) * x + 1.725627235645e-10) * x -
                   3.6863838563e-9) * x + 2.87495324207095e-8) * x +
                 1.71307311000282e-6) * x - 7.94273603184629e-5) * x +
               .00200938064965897) * x - .0363329491677178) * x +
            .434393683888443;
        r4 = ((((((((((x * -1.27815158195209e-14 + 1.99910415869821e-14) * x +
                      3.753542914426e-12) * x - 2.708018219579e-11) * x -
                    1.190574776587e-9) * x + 1.106696436509e-8) * x +
                  3.954955671326e-7) * x - 4.398596059588e-6) * x -
                2.01087998907735e-4) * x + .00789092425542937) * x -
              .142056749162695) * x + 1.39964149420683;
        r5 = ((((((((((x * -1.19442341030461e-13 - 2.34074833275956e-12) * x +
                      6.861649627426e-12) * x + 6.082671496226e-10) * x +
                    5.38116010542e-9) * x - 6.2532971387e-8) * x -
                  2.13596683505e-6) * x - 2.373394341886e-5) * x +
                2.88711171412814e-6) * x + .0485221195290753) * x -
              1.04346091985269) * x + 7.89901551676692;
        rts[m] = r1 / (r1 + 1.);
        rts[m + 1] = r2 / (r2 + 1.);
        rts[m + 2] = r3 / (r3 + 1.);
        rts[m + 3] = r4 / (r4 + 1.);
        rts[m + 4] = r5 / (r5 + 1.);
        m += 5;
        goto L500;


/*             ...T-range: 10 =< T < 15 */
      L5400:
        x = t - 12.5;
        wts[m] *= (((((((((x * 8.98007931950169e-15 + 7.25673623859497e-14) *
                         x + 5.851494250405e-14) * x -
                        4.234204823846e-11) * x + 3.911507312679e-10) * x -
                      9.65094802088511e-9) * x + 3.42197444235714e-7) * x -
                    7.51821178144509e-6) * x + 1.94218051498662e-4) * x -
                  .00538533819142287) * x + .168122596736809;
        wts[m + 1] *=
            ((((((((((x * -1.05490525395105e-15 + 1.96855386549388e-14) * x -
                     5.500330153548e-13) * x + 1.003849567976e-11) * x -
                   1.720997242621e-10) * x + 3.533277061402e-9) * x -
                 6.389171736029e-8) * x + 1.046236652393e-6) * x -
               1.73148206795827e-5) * x + 2.57820531617185e-4) * x -
             .0034618826533835) * x + .0703302497508176;
        wts[m + 2] *=
            (((((((((((x * 3.60020423754545e-16 - 6.24245825017148e-15) * x +
                      9.945311467434e-14) * x - 1.749051512721e-12) * x +
                    2.768503957853e-11) * x - 4.08688551136506e-10) * x +
                  6.0418906330361e-9) * x - 8.23540111024147e-8) * x +
                1.01503783870262e-6) * x - 1.20490761741576e-5) * x +
              1.26928442448148e-4) * x - .00105539461930597) * x +
            .0115543698537013;
        wts[m + 3] *=
            (((((((((((((x * 2.51163533058925e-18 -
                         4.31723745510697e-17) * x + 6.557620865832e-16) * x -
                       1.016528519495e-14) * x + 1.491302084832e-13) * x -
                     2.06638666222265e-12) * x + 2.67958697789258e-11) * x -
                   3.23322654638336e-10) * x + 3.63722952167779e-9) * x -
                 3.75484943783021e-8) * x + 3.49164261987184e-7) * x -
               2.92658670674908e-6) * x + 2.12937256719543e-5) * x -
             1.19434130620929e-4) * x + 6.45524336158384e-4;
        wts[m + 4] *=
            ((((((((((((((x * -1.29043630202811e-19 +
                          2.16234952241296e-18) * x -
                         3.107631557965e-17) * x + 4.570804313173e-16) * x -
                       6.301348858104e-15) * x + 8.031304476153e-14) * x -
                     9.446196472547e-13) * x + 1.018245804339e-11) * x -
                   9.96995451348129e-11) * x + 8.77489010276305e-10) * x -
                 6.84655877575364e-9) * x + 4.64460857084983e-8) * x -
               2.66924538268397e-7) * x + 1.24621276265907e-6) * x -
             4.30868944351523e-6) * x + 9.94307982432868e-6;
        r1 = ((((((((((x * -4.16387977337393e-17 + 7.2087299737386e-16) * x +
                      1.395993802064e-14) * x + 3.660484641252e-14) * x -
                    4.154857548139e-12) * x + 2.301379846544e-11) * x -
                  1.033307012866e-9) * x + 3.997777641049e-8) * x -
                9.35118186333939e-7) * x + 2.38589932752937e-5) * x -
              5.35185183652937e-4) * x + .00885218988709735;
        r2 = ((((((((((x * -4.56279214732217e-16 + 6.24941647247927e-15) * x +
                      1.737896339191e-13) * x + 8.964205979517e-14) * x -
                    3.538906780633e-11) * x + 9.561341254948e-11) * x -
                  9.77283189131e-9) * x + 4.24034019462e-7) * x -
                1.02384302866534e-5) * x + 2.57987709704822e-4) * x -
              .00554735977651677) * x + .0868245143991948;
        r3 = ((((((((((x * -2.52879337929239e-15 + 2.13925810087833e-14) * x +
                      7.884307667104e-13) * x - 9.02339815951e-13) * x -
                    5.814101544957e-11) * x - 1.333480437968e-9) * x -
                  2.217064940373e-8) * x + 1.643290788086e-6) * x -
                4.39602147345028e-5) * x + .00108648982748911) * x -
              .0213014521653498) * x + .294150684465425;
        r4 = ((((((((((x * -6.42391438038888e-15 + 5.37848223438815e-15) * x +
                      8.960828117859e-13) * x + 5.214153461337e-11) * x -
                    1.106601744067e-10) * x - 2.007890743962e-8) * x +
                  1.543764346501e-7) * x + 4.520749076914e-6) * x -
                1.88893338587047e-4) * x + .00473264487389288) * x -
              .0791197893350253) * x + .860057928514554;
        r5 = (((((((((((x * -2.24366166957225e-14 +
                        4.87224967526081e-14) * x + 5.587369053655e-12) * x -
                      3.045253104617e-12) * x - 1.22398388308e-9) * x -
                    2.05603889396319e-9) * x + 2.58604071603561e-7) * x +
                  1.34240904266268e-6) * x - 5.72877569731162e-5) * x -
                9.56275105032191e-4) * x + .0423367010370921) * x -
              .576800927133412) * x + 3.87328263873381;
        rts[m] = r1 / (r1 + 1.);
        rts[m + 1] = r2 / (r2 + 1.);
        rts[m + 2] = r3 / (r3 + 1.);
        rts[m + 3] = r4 / (r4 + 1.);
        rts[m + 4] = r5 / (r5 + 1.);
        m += 5;
        goto L500;


/*             ...T-range: 15 =< T < 20 */
      L5500:
        x = t - 17.5;
        wts[m] *= ((((((((((x * 1.74841995087592e-15 - 6.95671892641256e-16) *
                          x - 3.000659497257e-13) * x +
                         2.021279817961e-13) * x + 3.8535969354e-11) * x +
                       1.461418533652e-10) * x - 1.014517563435e-8) * x +
                     1.132736008979e-7) * x - 2.86605475073259e-6) * x +
                   1.21958354908768e-4) * x - .00386293751153466) * x +
            .145298342081522;
        wts[m + 1] *=
            ((((((((((x * -1.11199320525573e-15 + 1.85007587796671e-15) * x +
                     1.220613939709e-13) * x + 1.275068098526e-12) * x -
                   5.341838883262e-11) * x + 6.161037256669e-10) * x -
                 1.00914787975e-8) * x + 2.907862965346e-7) * x -
               6.12300038720919e-6) * x + 1.00104454489518e-4) * x -
             .00180677298502757) * x + .057800991453663;
        wts[m + 2] *=
            ((((((((((x * -9.49816486853687e-16 + 6.67922080354234e-15) * x +
                     2.606163540537e-15) * x + 1.98379995015e-12) * x -
                   5.400548574357e-11) * x + 6.638043374114e-10) * x -
                 8.799518866802e-9) * x + 1.791418482685e-7) * x -
               2.96075397351101e-6) * x + 3.38028206156144e-5) * x -
             3.58426847857878e-4) * x + .00839213709428516;
        wts[m + 3] *=
            (((((((((((x * 1.3382997106018e-17 - 3.4484187784414e-16) * x +
                      4.745009557656e-15) * x - 6.033814209875e-14) * x +
                    1.049256040808e-12) * x - 1.70859789556117e-11) * x +
                  2.15219425727959e-10) * x - 2.52746574206884e-9) * x +
                3.2776171442296e-8) * x - 3.90387662925193e-7) * x +
              3.4634020459387e-6) * x - 2.43236345136782e-5) * x +
            3.54846978585226e-4;
        wts[m + 4] *=
            (((((((((((((x * 2.69412277020887e-20 -
                         4.24837886165685e-19) * x + 6.030500065438e-18) * x -
                       9.069722758289e-17) * x + 1.246599177672e-15) * x -
                     1.56872999797549e-14) * x + 1.87305099552692e-13) * x -
                   2.09498886675861e-12) * x + 2.11630022068394e-11) * x -
                 1.92566242323525e-10) * x + 1.62012436344069e-9) * x -
               1.23621614171556e-8) * x + 7.72165684563049e-8) * x -
             3.59858901591047e-7) * x + 2.43682618601e-6;
        r1 = ((((((((((x * 1.9187576454574e-16 + 7.8357401095707e-16) * x -
                      3.260875931644e-14) * x - 1.186752035569e-13) * x +
                    4.275180095653e-12) * x + 3.357056136731e-11) * x -
                  1.123776903884e-9) * x + 1.231203269887e-8) * x -
                3.99851421361031e-7) * x + 1.45418822817771e-5) * x -
              3.49912254976317e-4) * x + .00667768703938812;
        r2 = ((((((((((x * 2.02778478673555e-15 + 1.01640716785099e-14) * x -
                      3.385363492036e-13) * x - 1.615655871159e-12) * x +
                    4.527419140333e-11) * x + 3.853670706486e-10) * x -
                  1.184607130107e-8) * x + 1.347873288827e-7) * x -
                4.47788241748377e-6) * x + 1.54942754358273e-4) * x -
              .00355524254280266) * x + .0644912219301603;
        r3 = ((((((((((x * 7.79850771456444e-15 + 6.00464406395001e-14) * x -
                      1.249779730869e-12) * x - 1.020720636353e-11) * x +
                    1.814709816693e-10) * x + 1.766397336977e-9) * x -
                  4.60355944901e-8) * x + 5.863956443581e-7) * x -
                2.03797212506691e-5) * x + 6.31405161185185e-4) * x -
              .0130102750145071) * x + .210244289044705;
        r4 = (((((((((((x * -2.92397030777912e-15 +
                        1.94152129078465e-14) * x + 4.85944766585e-13) * x -
                      3.217227223463e-12) * x - 7.484522135512e-11) * x +
                    7.19101516047753e-10) * x + 6.88409355245582e-9) * x -
                  1.44374545515769e-7) * x + 2.74941013315834e-6) * x -
                1.02790452049013e-4) * x + .00259924221372643) * x -
              .0435712368303551) * x + .562170709585029;
        r5 = (((((((((((x * 1.1797612684006e-14 + 1.24156229350669e-13) * x -
                       3.89274162228e-12) * x - 7.755793199043e-12) * x +
                     9.492190032313e-10) * x - 4.98680128123353e-9) * x -
                   1.81502268782664e-7) * x + 2.69463269394888e-6) * x +
                 2.5003215442164e-5) * x - .00133684303917681) * x +
               .0229121951862538) * x - .245653725061323) * x +
            1.89999883453047;
        rts[m] = r1 / (r1 + 1.);
        rts[m + 1] = r2 / (r2 + 1.);
        rts[m + 2] = r3 / (r3 + 1.);
        rts[m + 3] = r4 / (r4 + 1.);
        rts[m + 4] = r5 / (r5 + 1.);
        m += 5;
        goto L500;


/*             ...T-range: 20 =< T < 25 */
      L5600:
        x = t - 22.5;
        wts[m] *= (((((((((x * -9.10338640266542e-15 + 1.00438927627833e-13) *
                         x + 7.817349237071e-13) * x -
                        2.547619474232e-11) * x + 1.479321506529e-10) * x +
                      1.52314028857627e-9) * x + 9.20072040917242e-9) * x -
                    2.19427111221848e-6) * x + 8.65797782880311e-5) * x -
                  .00282718629312875) * x + .128718310443295;
        wts[m + 1] *=
            (((((((((x * 5.5238092761876e-15 - 6.43424400204124e-14) * x -
                    2.358734508092e-13) * x + 8.261326648131e-12) * x +
                  9.229645304956e-11) * x - 5.68108973828949e-9) * x +
                1.22477891136278e-7) * x - 2.11919643127927e-6) * x +
              4.23605032368922e-5) * x - .00114423444576221) * x +
            .0506607252890186;
        wts[m + 2] *=
            (((((((((x * 3.99457454087556e-15 - 5.11826702824182e-14) * x -
                    4.157593182747e-14) * x + 4.214670817758e-12) * x +
                  6.705582751532e-11) * x - 3.36086411698418e-9) * x +
                6.07453633298986e-8) * x - 7.40736211041247e-7) * x +
              8.84176371665149e-6) * x - 1.72559275066834e-4) * x +
            .00716639814253567;
        wts[m + 3] *=
            (((((((((((x * -2.14649508112234e-18 - 2.45525846412281e-18) * x +
                      6.126212599772e-16) * x - 8.526651626939e-15) * x +
                    4.826636065733e-14) * x - 3.3955416364974e-13) * x +
                  1.67070784862985e-11) * x - 4.42671979311163e-10) * x +
                6.773680559084e-9) * x - 7.03520999708859e-8) * x +
              6.04993294708874e-7) * x - 7.80555094280483e-6) * x +
            2.85954806605017e-4;
        wts[m + 4] *=
            ((((((((((((x * -5.63938733073804e-21 +
                        6.92182516324628e-20) * x - 1.586937691507e-18) * x +
                      3.357639744582e-17) * x - 4.810285046442e-16) * x +
                    5.386312669975e-15) * x - 6.117895297439e-14) * x +
                  8.441808227634e-13) * x - 1.18527596836592e-11) * x +
                1.36296870441445e-10) * x - 1.17842611094141e-9) * x +
              7.80430641995926e-9) * x - 5.9776741740054e-8) * x +
            1.65186146094969e-6;
        r1 = (((((((((x * -1.13927848238726e-15 + 7.39404133595713e-15) * x +
                     1.445982921243e-13) * x - 2.676703245252e-12) * x +
                   5.823521627177e-12) * x + 2.17264723874381e-10) * x +
                 3.56242145897468e-9) * x - 3.03763737404491e-7) * x +
               9.46859114120901e-6) * x - 2.30896753853196e-4) * x +
            .00524663913001114;
        r2 = ((((((((((x * 2.89872355524581e-16 - 1.22296292045864e-14) * x +
                      6.1840650972e-14) * x + 1.64984659123e-12) * x -
                    2.729713905266e-11) * x + 3.70991379065e-11) * x +
                  2.216486288382e-9) * x + 4.616160236414e-8) * x -
                3.32380270861364e-6) * x + 9.84635072633776e-5) * x -
              .00230092118015697) * x + .0500845183695073;
        r3 = ((((((((((x * 1.97068646590923e-15 - 4.894192706268e-14) * x +
                      1.136466605916e-13) * x + 7.546203883874e-12) * x -
                    9.635646767455e-11) * x - 8.295965491209e-11) * x +
                  7.534109114453e-9) * x + 2.699970652707e-7) * x -
                1.42982334217081e-5) * x + 3.78290946669264e-4) * x -
              .00803133015084373) * x + .158689469640791;
        r4 = ((((((((((x * 1.33642069941389e-14 - 1.55850612605745e-13) * x -
                      7.522712577474e-13) * x + 3.209520801187e-11) * x -
                    2.075594313618e-10) * x - 2.070575894402e-9) * x +
                  7.323046997451e-9) * x + 1.851491550417e-6) * x -
                6.37524802411383e-5) * x + .00136795464918785) * x -
              .0242051126993146) * x + .397847167557815;
        r5 = ((((((((((x * -6.07053986130526e-14 + 1.04447493138843e-12) * x -
                      4.286617818951e-13) * x - 2.632066100073e-10) * x +
                    4.804518986559e-9) * x - 1.835675889421e-8) * x -
                  1.068175391334e-6) * x + 3.292234974141e-5) * x -
                5.94805357558251e-4) * x + .00829382168612791) * x -
              .0993122509049447) * x + 1.09857804755042;
        rts[m] = r1 / (r1 + 1.);
        rts[m + 1] = r2 / (r2 + 1.);
        rts[m + 2] = r3 / (r3 + 1.);
        rts[m + 3] = r4 / (r4 + 1.);
        rts[m + 4] = r5 / (r5 + 1.);
        m += 5;
        goto L500;


/*             ...T-range: 25 =< T < 40 */
      L5700:
        e = exp (-t);
        w1 = e * -.01962 + sqrt (.785398163397448 / t);
        w2 = ((((((((t * 2.7777834587065e-5 - .0022283501765589) * t +
                    .161077633475573) * t - 8.96743743396132) * t +
                  328.062687293374) * t - 7657.22701219557) * t +
                110255.055017664) * t - 892528.122219324) * t +
              3106386.27744347) * e + w1 * .270967405960535;
        w3 = ((((((((t * 1.83574464457207e-5 - .00154837969489927) * t +
                    .118520453711586) * t - 6.69649981309161) * t +
                  244.789386487321) * t - 5688.32664556359) * t +
                81450.7604229357) * t - 655181.056671474) * t +
              2264108.96607237) * e + w1 * .0382231610015404;
        w4 = (((((((((t * -2.4079943580995e-8 + 8.12621667601546e-6) * t -
                     9.04491430884113e-4) * t + .0637686375770059) * t -
                   2.96135703135647) * t + 91.514235699633) * t -
                 1869.71865249111) * t + 24294.5528916947) * t -
               181852.473229081) * t + 596854.758661427) * e + w1 *
            .00151614186862443;
        w5 = (((((((((t * -4.6110090613397e-10 + 1.43069932644286e-7) * t -
                     1.6396091543108e-5) * t + .00115791154612838) * t -
                   .0530573476742071) * t + 1.61156533367153) * t -
                 32.3248143316007) * t + 412.007318109157) * t -
               3022.60070158372) * t + 9715.75094154768) * e + w1 *
            8.62130526143657e-6;
        wts[m] *= w1 - w2 - w3 - w4 - w5;
        wts[m + 1] *= w2;
        wts[m + 2] *= w3;
        wts[m + 3] *= w4;
        wts[m + 4] *= w5;
        r1 = ((((((((t * -1.73363958895356e-6 + 1.19921331441483e-4) * t -
                    .0159437614121125) * t + 1.13467897349442) * t -
                  44.7216460864586) * t + 1062.51216612604) * t -
                15207.3917378512) * t + 120662.887111273) * t -
              407186.366852475) * e + .117581320211778 / (t -
                                                          .117581320211778);
        r2 = ((((((((t * -1.6010254262171e-5 + .00110331262112395) * t -
                    .150043662589017) * t + 10.5563640866077) * t -
                  410.468817024806) * t + 9626.04416506819) * t -
                135888.06983827) * t + 1061075.7703834) * t -
              3511907.92816119) * e + 1.0745620124369 / (t - 1.0745620124369);
        r3 = ((((((((t * -4.48880032128422e-5 + .00269025112122177) * t -
                    .401048115525954) * t + 27.8360021977405) * t -
                  1048.91729356965) * t + 23698.5942687423) * t -
                319504.627257548) * t + 2348796.93563358) * t -
              7163415.68174085) * e + 3.08593744371754 / (t -
                                                          3.08593744371754);
        r4 = ((((((((t * -6.38526371092582e-5 - .00229263585792626) * t -
                    .0765735935499627) * t + 9.12692349152792) * t -
                  232.077034386717) * t + 281.839578728845) * t +
                95952.9683876419) * t - 1776389.56809518) * t +
              10248975.964541) * e + 6.41472973366203 / (t -
                                                         6.41472973366203);
        r5 = ((((((((t * -3.59049364231569e-5 - .0225963977930044) * t +
                    1.12594870794668) * t - 45.6752462103909) * t +
                  1058.04526830637) * t - 11600.3199605875) * t -
                40729.7627297272) * t + 2222155.28319857) * t -
              16119645.5032613) * e + 11.8071894899717 / (t -
                                                          11.8071894899717);
        rts[m] = r1 / (r1 + 1.);
        rts[m + 1] = r2 / (r2 + 1.);
        rts[m + 2] = r3 / (r3 + 1.);
        rts[m + 3] = r4 / (r4 + 1.);
        rts[m + 4] = r5 / (r5 + 1.);
        m += 5;
        goto L500;


/*             ...T-range: 40 =< T < 59 */
      L5800:
        x = t * t * t;
        e = exp (-t) * x;
        r1 = (((t * -.0243758528330205 + 2.07301567989771) * t -
               64.5964225381113) * t + 714.16008865547) * e +
            .117581320211778 / (t - .117581320211778);
        r2 = (((t * -.228861955413636 + 19.3190784733691) * t -
               599.774730340912) * t + 6618.44165304871) * e +
            1.0745620124369 / (t - 1.0745620124369);
        r3 = (((t * -.695053039285586 + 57.6874090316016) * t -
               1777.0414322552) * t + 19536.6082947811) * e +
            3.08593744371754 / (t - 3.08593744371754);
        r4 = (((t * -1.58072809087018 + 127.050801091948) * t -
               3866.8735091428) * t + 42302.482812142) * e +
            6.41472973366203 / (t - 6.41472973366203);
        r5 = (((t * -3.33963830405396 + 251.830424600204) * t -
               7577.28527654961) * t + 82196.681659569) * e +
            11.8071894899717 / (t - 11.8071894899717);
        rts[m] = r1 / (r1 + 1.);
        rts[m + 1] = r2 / (r2 + 1.);
        rts[m + 2] = r3 / (r3 + 1.);
        rts[m + 3] = r4 / (r4 + 1.);
        rts[m + 4] = r5 / (r5 + 1.);
        e *= x;
        w1 = sqrt (.785398163397448 / t);
        w2 = ((t * 2.09539509123135e-5 - 6.87646614786982e-4) * t +
              .00668743788585688) * e + w1 * .270967405960535;
        w3 = ((t * 1.34547929260279e-5 - 4.19389884772726e-4) * t +
              .00387706687610809) * e + w1 * .0382231610015404;
        w4 = ((t * 1.23464092261605e-6 - 3.5522456427559e-5) * t +
              3.03274662192286e-4) * e + w1 * .00151614186862443;
        w5 = ((t * 1.35482430510942e-8 - 3.27722199212781e-7) * t +
              2.41522703684296e-6) * e + w1 * 8.62130526143657e-6;
        wts[m] *= w1 - w2 - w3 - w4 - w5;
        wts[m + 1] *= w2;
        wts[m + 2] *= w3;
        wts[m + 3] *= w4;
        wts[m + 4] *= w5;
        m += 5;
        goto L500;


/*             ...T-range: T >= 59 */
      L5900:
        w1 = sqrt (.785398163397448 / t);
        w2 = w1 * .270967405960535;
        w3 = w1 * .0382231610015404;
        w4 = w1 * .00151614186862443;
        w5 = w1 * 8.62130526143657e-6;
/*         R1 = R15 / (T - R15) */
/*         R2 = R25 / (T - R25) */
/*         R3 = R35 / (T - R35) */
/*         R4 = R45 / (T - R45) */
/*         R5 = R55 / (T - R55) */
/*         RTS (M)   = R1 / (ONE + R1) */
/*         RTS (M+1) = R2 / (ONE + R2) */
/*         RTS (M+2) = R3 / (ONE + R3) */
/*         RTS (M+3) = R4 / (ONE + R4) */
/*         RTS (M+4) = R5 / (ONE + R5) */
        wts[m] *= w1 - w2 - w3 - w4 - w5;
        wts[m + 1] *= w2;
        wts[m + 2] *= w3;
        wts[m + 3] *= w4;
        wts[m + 4] *= w5;
        rts[m] = .117581320211778 / t;
        rts[m + 1] = 1.0745620124369 / t;
        rts[m + 2] = 3.08593744371754 / t;
        rts[m + 3] = 6.41472973366203 / t;
        rts[m + 4] = 11.8071894899717 / t;
        m += 5;
      L500:
        ;
    }
}

#ifdef __INTEL_OFFLOAD
#pragma offload_attribute(pop)
#endif