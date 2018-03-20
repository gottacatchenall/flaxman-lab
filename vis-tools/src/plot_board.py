import matplotlib.pyplot as plt
import matplotlib.animation as animation
from matplotlib.patches import Circle
import numpy as np

size = 0

def setup(GRID_SIZE):
    global size
    size = GRID_SIZE
    figure = plt.figure(figsize=(7,7))
    ax = plt.gca()
    ax.grid(linestyle='-', linewidth=.5)

    # Minor ticks
    ax.set_xticks(np.arange(-.5, GRID_SIZE, 1));
    ax.set_yticks(np.arange(-.5, GRID_SIZE, 1));

    # Gridlines based on minor ticks
    ax.grid(color='black', linestyle='-', linewidth=.3)
    ax.set_xlim([-.5, GRID_SIZE-.5])
    ax.set_ylim([-.5, GRID_SIZE-.5])
    plt.tick_params(axis='both', which='both', left='off', labelleft='off', bottom='off', labelbottom='off')

    return figure, ax

def show(figure, ax, m, save=False, ani=False):
    if (ani):
        im = plt.imshow(m[0], interpolation='none', aspect='equal', cmap="gist_earth")
    else:
        im = plt.imshow(m, interpolation='none', aspect='equal', cmap="gist_earth")
    def update(i):
        ax.grid(color='black', linestyle='-', linewidth=.3)
        im.set_array(m[i])
        time_text.set_text('Generation: ' + str(i))
        return im,
    if ani:
        ani = animation.FuncAnimation(figure, update, frames=[i for i in range(len(m))], interval=1, blit=False)
        Writer = animation.writers['ffmpeg']
        writer = Writer(fps=30, metadata=dict(artist='Me'),)
        if save:
            ani.save('map.mp4', dpi=300)
    time_text = ax.text(0, size+1, 'Generation: 0', fontsize=12)
    plt.show()

def show_w_indivs(figure, ax, m, pop_map, save=False, ani=False):
    def update(i):
        for patch in ax.patches:
            patch.remove()
        ax.grid(color='black', linestyle='-', linewidth=.3)
        im.set_array(m[i])
        time_text.set_text('Generation: ' + str(i))

        patches = []

        gen_data_exists = False
        pop = None
        for x in pop_map:
            if x['gen'] == i:
                gen_data_exists = True
                pop = x['map']
                break

        if (gen_data_exists):
            for i in range(len(pop)):
                for j in range(len(pop)):
                    n = pop[i][j]
                    if (n > 0):
                        rad = float(n)/float(len(pop)) * .45
                        if rad < 0.15:
                            rad = 0.15
                        c = Circle((i,j), radius=rad, edgecolor='purple', facecolor='purple', alpha=0.5)
                        ax.add_patch(c)
            patches.append(ax.add_patch(c))
            return patches,
        return im
    if ani:
        circs = []
        pop = pop_map[0]['map']
        for i in range(len(pop)):
            for j in range(len(pop)):
                n_indiv = pop[i][j]
                if (n_indiv > 0):
                    rad = float(n_indiv)/float(50) * .45
                    if rad < 0.15:
                        rad = 0.15
                    c = Circle((i,j), radius=rad, edgecolor='purple', facecolor='purple', alpha=0.5)
                    ax.add_patch(c)
        im = plt.imshow(m[0], interpolation='none', aspect='equal', cmap="gist_earth")
    else:
        circs = []
        pop = pop_map[0]['map']
        for i in range(len(pop)):
            for j in range(len(pop)):
                n_indiv = pop[i][j]
                if (n_indiv > 0):
                    rad = float(n_indiv)/float(50) * .45
                    if rad < 0.15:
                        rad = 0.15
                    c = Circle((i,j), radius=rad, edgecolor='purple', facecolor='purple', alpha=0.5)
                    ax.add_patch(c)
        plt.imshow(m[0], interpolation='none', aspect='equal', cmap="gist_earth")


    if ani:
        ani = animation.FuncAnimation(figure, update, frames=[i for i in range(len(pop_map))], interval=1, blit=False)
        Writer = animation.writers['ffmpeg']
        writer = Writer(fps=30, metadata=dict(artist='Me'),)
        if save:
            ani.save('map.mp4', dpi=300)

    time_text = ax.text(0, size+3, 'Generation: 0', fontsize=12)
    plt.show()
