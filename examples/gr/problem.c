/**
 * Post-Newtonian correction from general relativity
 * 
 * This example shows how to add post-newtonian corrections to REBOUND simulations with reboundx.
 * If you have GLUT installed for the visualization, press 'w' and/or 'c' for a clearer view of
 * the whole orbit.
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include "rebound.h"
#include "reboundx.h"

//void heartbeat(struct reb_simulation* sim);
//double E_0;

int main(int argc, char* argv[]){
    struct reb_simulation* sim = reb_create_simulation();
    sim->heartbeat = heartbeat;

    struct reb_particle p = {0}; 
    p.m     = 1.;   
    reb_add(sim, p); 

    double m = 1.e-6;
    double a = 1.e-4; // put planet close to enhance precession so it's visible in visualization (this would put planet inside the Sun!)
    double e = 0.2;
    double omega = 0.;
    double f = 0.;

    struct reb_particle p1 = reb_tools_orbit2d_to_particle(sim->G, p, m, a, e, omega, f);
    reb_add(sim,p1);
    reb_move_to_com(sim);
    
    struct rebx_extras* rebx = rebx_init(sim); // initialize reboundx
    double c = C_DEFAULT; // Have to set the speed of light in appropriate units (set by G and your initial conditions).  Here we use the value in default units of AU/(yr/2pi) 
    rebx_add_gr(rebx, &sim->particles[0], c); // add postnewtonian correction, treating only particles[0] as massive for GR corrections
    /*See reboundx.readthedocs.org for more options.*/
    double tmax = 5.e-2;

    //E_0 = rebxtools_gr_energy(sim);
    reb_integrate(sim, tmax); 
    rebx_free(rebx);    // this explicitly frees all the memory allocated by REBOUNDx 
}

/*void heartbeat(struct reb_simulation* sim){
    if (reb_output_check(sim, 1.e-4)){
        double energy = rebxtools_gr_energy(sim); 
        printf("%f\t%e\n", sim->t, fabs(energy-E_0)/fabs(E_0));
    }
}*/
            
