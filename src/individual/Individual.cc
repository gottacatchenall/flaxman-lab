
#include "Individual.h"
#include "Random.h"
#include "Patch.h"
#include "params_struct.h"
#include "GeneTracker.h"
#include "genetic_map.h"

int Individual::id_counter = 0;

Individual::Individual(Patch* patch, int sex, bool parent_is_migrant){
    this->id = this->id_counter++;
    this->sex = sex;
    this->w = 0.0;
    this->migrated = false;
    this->parent_migrated = parent_is_migrant;
    this->patch = patch;

    int n_loci = params->N_LOCI;
    this->haplotype0 = new double[n_loci];
    this->haplotype1 = new double[n_loci];
}

Individual::~Individual(){
    delete this->haplotype0;
    delete this->haplotype1;
}

// ==========================================
// Core Methods
// ==========================================
    // Each of these methods are called once per generation

/*  Individual::migrate(std::vector<Patch*> surrounding_patches)
        Calculates an individual's preference for each patch in the vector surrounding_patches,
        and then migrates to the one with the highest preference.
*/
void Individual::migrate(std::vector<Patch*> surrounding_patches){

    double pref;

    int n_patches = surrounding_patches.size();
    std::vector<double> patch_pref_vals;
    std::vector<double> normalized_patch_pref_vals;

    for (Patch* patch : surrounding_patches){
        pref = this->calc_pref(patch);
        patch_pref_vals.push_back(pref);
    }

    double sum_of_pref = 0.0;

    for (double val : patch_pref_vals){
        sum_of_pref += val;
    }

    double sigma = params->PREFERENCE_STRENGTH;

    for (double val : patch_pref_vals){
        double tmp = val/double(sum_of_pref);
        double tmp_w_noise = random_gen->normal(tmp, sigma);
        normalized_patch_pref_vals.push_back(tmp_w_noise);
    }

    double max = 0.0;
    double upper, val;
    int index = normalized_patch_pref_vals.size() - 1;


    for (int i = 0; i < normalized_patch_pref_vals.size(); i++){
        val = normalized_patch_pref_vals[i];
        if (val > max){
            index = i;
            max = val;
        }
    }

    Patch* new_patch = surrounding_patches[index];

    if (this->patch != new_patch){
        this->migrated = true;
        this->patch->remove_individual(this);
        new_patch->add_individual(this);
        this->patch = new_patch;
    }
}

/*  Individual::selection(double max_fit)
        Determines whether an individual survives selection by using the Beverton-Holt
        model and the individual's relative fitness.
*/
bool Individual::selection(double max_fit){
    double fitness = double(this->w)/double(max_fit);
    double k_prime = double(params->CARRYING_CAPACITY * fitness);
    double prob = this->beverton_holt_prob(k_prime);

    if (random_gen->uniform_float(0,1) < prob){
            return true;
    }
    return false;
}

/*  Individual::census_indiv()
        Censuses this individuals genotype to measure allelic frequencies
*/
void Individual::census_indiv(){
    int n_loci = params->N_LOCI;
    int x = this->patch->get_x();
    int y = this->patch->get_y();

    int locus;
    double allele;

    for (locus = 0; locus < n_loci; locus++){
        allele = this->get_allele(locus, 0);
        gene_tracker->update_tracker(locus, allele, x, y);
        allele = this->get_allele(locus, 1);
        gene_tracker->update_tracker(locus, allele, x, y);
    }
}

/*  Individual::census_dependent_alleles()
        Censuses the individuals genotype repeatedly with respect to the allele at each locus,
        used to calculate LD values.
*/
void Individual::census_dependent_alleles(){
    // void add_dependent_allele(allele* primary_allele, int dependent_locus, double dependent_allele_val, int x, int y){
    // gene_tracker->find_allele(int locus, double allele_val)
    int n_loci = params->N_LOCI;
    int x = this->patch->get_x();
    int y = this->patch->get_y();

    allele* al1_1;
    allele* al1_2;

    for (int l1 = 0; l1 < n_loci; l1++){
        al1_1 = gene_tracker->find_allele(l1, this->get_allele(l1, 0));
        al1_2 = gene_tracker->find_allele(l1, this->get_allele(l1, 1));

        for (int l2 = l1+1; l2 < n_loci; l2++){
            gene_tracker->add_dependent_allele(al1_1, l2, this->get_allele(l2, 0), x, y);
            gene_tracker->add_dependent_allele(al1_1, l2, this->get_allele(l2, 1), x, y);
            gene_tracker->add_dependent_allele(al1_2, l2, this->get_allele(l2, 0), x, y);
            gene_tracker->add_dependent_allele(al1_2, l2, this->get_allele(l2, 1), x, y);
        }
    }
}

// ==========================================
// Utility functions
// ==========================================

/*  Individual::fitness_gaussian(double diff)
        Returns the value of the fitness gaussian based on the difference
        between EF value and allele value.
*/
double Individual::fitness_gaussian(double diff){
    double sigma = params->SELECTION_STRENGTH;
    return exp(-1*(diff*diff)/(2*sigma*sigma));
}

/*  Individual::beverton_holt_prob(double k_prime)
        Returns the probably of surviving selection based on the Beverton-Holt model,
        where k_prime is an adjusted carrying capacity based on the individual's relative fitness.
*/
double Individual::beverton_holt_prob(double k_prime){
    int n = this->patch->get_n_indiv();
    int b = params->AVG_NUM_OFFSPRING_PER_FEMALE;

    double prop_full = double(n)/double(k_prime);
    double prob = double(1.0) / double(1 + (double(b)/double(2) - 1)*(prop_full));
    return prob;
}

/*  Individual::calc_fitness()
        Calculates an individual's overall fitness.
*/
double Individual::calc_fitness(){
    int n_ef = params->N_ENV_FACTORS;
    int n_loci_per_ef = params->N_LOCI_PER_ENV_FACTOR;
    int n_fitness_loci = n_ef * n_loci_per_ef;

    int locus;
    double theta_i, x_i, s_i, w_i;

    double w = 1.0;
    double s_max_i = 0.1;

    for (int i = 0; i < n_ef; i++){
        theta_i = patch->get_envFactor_value(i);

        for (int j = 0; j < n_loci_per_ef; j++ ){
            locus = genetic_map->fitness_loci[i][j];

            x_i = this->get_allele(locus, 0);
            s_i = s_max_i * exp(-(x_i - theta_i)*(x_i - theta_i)); // TODO make this draw from gaussian
            w_i = 1.0 + s_i;
            w = w * w_i;

            x_i = this->get_allele(locus, 1);
            s_i = s_max_i * exp(-(x_i - theta_i)*(x_i - theta_i));  // TODO make this draw from gaussian
            w_i = 1.0 + s_i;
            w = w * w_i;
        }
    }

    this->w = w;
    return w;
}

/*  Individual::calc_pref(Patch* patch)
        Calculates an indivudal's preference for the Patch* patch.
*/
double Individual::calc_pref(Patch* patch){

    int n_ef = params->N_ENV_FACTORS;
    int n_loci_per_ef = params->N_LOCI_PER_ENV_FACTOR;
    int n_fitness_loci = n_ef * n_loci_per_ef;

    int locus;
    double theta_i, y_i, s_i, p_i;

    double pref = 1.0;
    double s_max_i = 0.1;

    double theor_max = 1.0;

    for (int i = 0; i < n_fitness_loci; i++){
        theor_max = theor_max * 1.1;
    }

    for (int i = 0; i < n_ef; i++){
        theta_i = patch->get_envFactor_value(i);

        for (int j = 0; j < n_loci_per_ef; j++ ){
            locus = genetic_map->pref_loci[i][j];

            y_i = this->get_allele(locus, 0);

            s_i = s_max_i * exp(-(y_i - theta_i)*(y_i - theta_i));
            p_i = 1.0 + s_i;
            pref = pref * p_i;

            y_i = this->get_allele(locus, 1);
            s_i = s_max_i * exp(-(y_i - theta_i)*(y_i - theta_i));
            p_i = 1.0 + s_i;
            pref = pref * p_i;
        }
    }

    return float(pref)/float(theor_max);
}

/*  Individual::make_gamete()
        Makes a gamete from the individual based on the linkage mode parameter.
*/
double* Individual::make_gamete(){
    if (params->LINKAGE_MODE == ALL_LOCI_INDEPENDENT){
        double* gamete = new double[params->N_LOCI];
        int n_loci = params->N_LOCI;
        int haplo;
        for (int i = 0; i < n_loci; i++){
            haplo = random_gen->uniform_int(0,1);
            gamete[i] = this->get_allele(i, haplo);
        }
        return gamete;
    }

    else if (params->LINKAGE_MODE == NORMAL_LINKAGE){
        return this->crossing_over();
    }

    assert(0 && "neither linkage mode was chosen");
}

/*  Individual::crossing_over()
        Generates a gamete by similating crossing over.
        (This is the most biologically realistic mode for gamete production)
*/
double* Individual::crossing_over(){
    double* gamete = new double[params->N_LOCI];
    int n_loci = params->N_LOCI;
    int n_crossover_events = random_gen->n_crossover_events();
    std::vector<int> crossing_over_points;

    // Generate a random permutation of unique loci to be the crossover points
    int r;
    bool exists;
    for(int i = 0; i < n_crossover_events; i++){
        do{
            r = random_gen->uniform_int(0,n_loci-1);
            exists = (std::find(crossing_over_points.begin(), crossing_over_points.end(), r) != crossing_over_points.end());
        } while(exists);
        crossing_over_points.push_back(r);
    }

    // Sort crossing_over_points
    std::sort(crossing_over_points.begin(), crossing_over_points.end());

    int curr_crossover = 0;
    int curr_chromo = 0;
    int current_haplo = random_gen->uniform_int(0,1);

    for (int i = 0; i < n_loci; i++){
        // Check if at start of a new chromosome
        if (i == genetic_map->chromo_map[curr_chromo]){
            curr_chromo++;
            current_haplo = random_gen->uniform_int(0,1);
        }

        if (n_crossover_events > 0){
            // Check if at a crossover point
            if (i == crossing_over_points[curr_crossover]){
                curr_crossover++;

                // switch haplo
                current_haplo = !(current_haplo);
            }
        }


        if (random_gen->uniform_float(0,1) < params->MUTATION_RATE){
            gamete[i] = random_gen->uniform_float(0,1);
        }

        else{
            gamete[i] = this->get_allele(i, current_haplo);
        }
    }

    return gamete;
}

/*  Individual::set_haplotype(int haplo_num, double* haplotype)
        Replaces an indviduals haplotype (either 0 or 1 based on haplo_num) with the
        array of doubles haplotype.
*/
void Individual::set_haplotype(int haplo_num, double* haplotype){
    if (haplo_num == 0){
        free(this->haplotype0);
        this->haplotype0 = haplotype;
        return;
    }
    else if (haplo_num == 1){
        free(this->haplotype1);
        this->haplotype1 = haplotype;
        return;
    }

    assert(0 && "set_haplotype called with invalid haplo_num");
}

// ==========================================
// Getters and Setters
// ==========================================

int Individual::get_id(){
    return this->id;
}

int Individual::get_sex(){
    return this->sex;
}

void Individual::set_allele(int locus, double value, int haplo){
    if (haplo == 0){
        this->haplotype0[locus] = value;
        return;
    }
    else if (haplo == 1){
        this->haplotype1[locus] = value;
        return;
    }

    assert(0 && "set_allele called with invalid haplotype number");
}

double Individual::get_allele(int locus, int haplo){
    if (haplo == 0){
        return this->haplotype0[locus];
    }
    else if (haplo == 1){
        return this->haplotype1[locus];
    }

    assert(0 && "get_allele called with invalid haplo_num");
}

bool Individual::is_migrant(){
    return this->migrated;
}

bool Individual::is_parent_migrant(){
    return this->parent_migrated;
}
