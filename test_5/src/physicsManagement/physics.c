/*RETURNING INT FOR NOW TO KEEP IT EASY TO READ :) THEN ONCE IT WORKS LET'S FLOAT THIS*/
int get_kinetic_energy(int kg, int meter_per_sec){
  /*Ek = 1/2 * m*v² */
  return 1/2*kg*meter_per_sec*meter_per_sec;
};

/**
 * [get_speed return the speed of an element]
 * @param distance [the distance in meter done]
 * @param interval [amount of seconds spent ]
 */
int get_speed (int distance, int interval){
  /*v = distance/interval*/
  return distance/interval;
}
