// ====================================
// Classes
// ====================================

class Individual(){
    // Data structure here TBD
    genome = {}
    x = nil
    y = nil

    // ====================================
    // Methods
    // ====================================

    // Picks initial location for the indivudal in the viscinity of (x,y). Alg TBD
    func get_location(x,y) { return (x_indiv, y_indiv) }

    // Gets the initial value for the fitness and preference alleles based on individual's location
    func get_initial_alleles(x,y){
        // Environmental Fitness Alleles
        for i in (0, K_VALUE){
            // Add an allele reasonably well adapted to individual's current location
        }

        // Preference Alleles
        for i in (0, K_VALUE){
            // Could be entirely random, TBD
        }

        // Beanbag Loci
        for i in (0, NUM_OF_BEANBAG_LOCI){
            // Initialize each locus with some allele
        }
    }

    // Chooses whether or not to migrate based on preference alleles, and if so where to go. Alg TBD
    func migrate(){}

    // Returns fitness calculated as a function of environmental fitness alleles and current location
    func get_fitness(){ return fitness }

    // Algorithm here TBD
    func choose_mate(){ return mate }

    // Algorithm here TBD
    func reproduce(mate){ return offspring }
}

class Hotspot(){
    // Hotspot parameters
    x_center = nil
    y_center = nil
    sigma = nil

    // ====================================
    // Methods
    // ====================================

    // Picks random sigma on an appropriate interval
    func get_random_sigma() { return sigma }

    // Gets a new hotspot location based on the mode. Alg TBD.
    func get_xy(HOTSPOT_MODE){ return (x,y) }

    // Returns the value of the Hotspot Gaussian at the location (x,y)
    func Gaussian(x,y){ return val }

    // Decreases sigma, probably by an amount drawn from a Poisson distribution
    func reduce_sigma(){}
}

class Board(){

    // Data structures here TBD
    grid = {}
    individuals = {}
    hotspots = {}

    // ====================================
    // Methods
    // ====================================

    // Picks the locations of the center of environmental parameter Gaussians ("Hotspots").
    func pick_hotspots(NUM_OF_HOTSPOTS, HOTSPOT_MODE){
        for i in (0, NUM_OF_HOTSPOTS){
            hotspot = Hotspot()

            hotspot.get_random_sigma()
            hotspot.get_xy(HOTSPOT_MODE)

            // Adds hotspot the board
            add_hotspot(hotspot)
        }
    }

    // Places the individuals on the board.
    func allocate_individuals(TOTAL_NUMBER_INDIVIDUALS, NUM_OF_POPULATIONS){
        for i in (0, NUM_OF_POPULATIONS){

            // Gets the number of indivudals in this population. Alg TBD.
            n = get_num_individuals(TOTAL_NUMBER_INDIVIDUALS)

            // Picks where the "center" of this population is. Algorithm here TBD.
            (x,y) = pick_population_center()

            for i in (0, n){
                indiv = Individual()

                indiv.get_location(x,y)
                indiv.get_initial_alleles()

                // Adds indivudal to the board
                add_individual(individual)
            }
        }
    }

    // Individuals migrate
    func migrate(){
        for (individual in individuals){
            indivudal.migrate()
        }
    }

    // Preps board and individuals for next generation
    func next_gen(){

        // Check fitness values to see which individuals survive
        for (individual in individuals){
            fitness = indivudal.get_fitness()
            if (fitness < FITNESS_THRESHOLD){
                individual.survives = false
            }
        }

        // Data structue TBD
        next_gen = {}

        // Reproduction
        for (individual in individuals){

            // Assumes indivudals only mate with only one other, may not be a good assumption
            if(individual.survives && indivudal.hasNotReproduced){
                mate = individual.choose_mate()
                indivudal.hasNotReproduced = false
                mate.hasNotReproduced = false
                offspring = individual.reproduce(mate)
                next_gen.add(offspring)
            }
        }

        // Replace current gen
        individuals = next_gen

        // Adjusts hotspots for next generation
        for (hotspot in hotspots){
            hotspot.reduce_sigma()
        }
    }
}


// ====================================
// Helper funcs
// ====================================

func board_setup(){
    // Creates a BOARD_SIZE x BOARD_SIZE instance of class Board
    board = Board(BOARD_SIZE)

    // HOTSPOT_MODE is a parameter that determines how hotspots are arranged (clustered, gradient, random, etc.)
    board.pick_hotspots(NUM_OF_HOTSPOTS, HOTSPOT_MODE)

    // NUM_OF_POPULATIONS is the number of populations within the metapopulation
    board.allocate_individuals(TOTAL_NUMBER_INDIVIDUALS, NUM_OF_POPULATIONS)

    return board
}


// ====================================
// Main func
// ====================================

func main(){
    board = board_setup()

    for i in (0, NUM_OF_GENERATIONS){
        board.migrate()
        board.next_gen()
    }
}
