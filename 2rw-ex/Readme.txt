2D Lattice Gas Random Walk

          Kazume Nishidate
nisidate@iwate-u.ac.jp

1) How to make.
   Type "make".
   
2) X Window version.

   Edit the main.c file.
   Comment-out the "show_matrix" line:
      /*	show_matrix(sys.msmat1);  */
   so that the lengthy display on the terminal will be
   suppressed.

   And type "make -f Makefile.X".

3) Control parameters such as the System size, concentration, time
   steps are specified in the file control.c.


Refs.:
1) Kazume NISHIDATE, Mamoru BABA, Hideyuki CHIBA, Takanori ITO, Kouichi KODAMA and Kiyoshi NISHIKAWA
Probabilistic Cellular Automaton for Random Walkers
Journal of the Physical Society of Japan, Vol. 69, pp. 1352-1355, 2000

2) Kazume NISHIDATE, Mamoru BABA and Richard J. GAYLORD
Cellular automaton model for Biased Diffusive Traffic Flow
Journal of the Physical Society of Japan, Vol. 65, pp. 3415-3418, 1996

3) Kazume Nishidate, Mamoru Baba, and Richard J. Gaylord
Cellular Automaton Model for Random Walkers
Physical Review Letters, Vol. 77, pp. 1675-1678, 1996

