#
#  Configura graficación en GNUplot
#  
# Ejecutar desde un Shell de linux $ gnuplot -p 'graf_senal.gp
# Ejecutar desde GNUplot; $load 'graf_senal.gp'
# Ejecutar desde una línea en código  c:
# system("gnuplot -p 'graf_senal.gp' ");
###
set autoscale
set output  "sub3.eps"
set grid
set style data lines

#------------- Graf 1 ----------------
set title "Submuestreo a Razon de 3"
#unset label
set xlabel   "n"
set ylabel   "x(n)"
plot  "sub_3.dat"           # Grafica el archivo de datos    
unset xlabel
unset ylabel
unset title


