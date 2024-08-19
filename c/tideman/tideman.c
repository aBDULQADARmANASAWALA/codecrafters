#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
} pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
bool is_cycle(int winner, int loser);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // checking for max candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }

    // creating the candidates array
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked pairs and preferences
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
            preferences[i][j] = 0;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // collection of votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        // changes with every candidate
        int ranks[candidate_count];

        // collection of votes for each rank
        for (int rank = 0; rank < candidate_count; rank++)
        {
            string name = get_string("Rank %i: ", rank + 1);

            // adding names to ranks array if voted candidate is found
            if (!vote(rank, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        // updating preferences array after every voter
        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}
//________________________________________________________________________

// Update ranks for every new vote
bool vote(int rank, string name, int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        // checking if the voted candidate is found
        if (strcmp(candidates[i], name) == 0)
        {
            // i is the index of candidate array aka candidate name.
            // rank is the rank of the candidate for that voter.
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences for every voter's votes
void record_preferences(int ranks[])
{
    for (int i = 0; i < candidate_count - 1; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            // the first element of ranks array will be preferred over all other elements
            // but from second onwards, we only want candidates after that
            if (j > i)
            {
                // ith element of ranks is preferred over jth element of ranks
                preferences[ranks[i]][ranks[j]]++;
            }
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 1; j < candidate_count; j++)
        {
            if (j > i)
            {
                if (preferences[i][j] > preferences[j][i])
                {
                    pairs[pair_count].winner = i;
                    pairs[pair_count].loser = j;
                    pair_count++;
                }
                else if (preferences[i][j] < preferences[j][i])
                {
                    pairs[pair_count].winner = j;
                    pairs[pair_count].loser = i;
                    pair_count++;
                }
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    pair extra;
    bool swapped;
    while (true)
    {
        swapped = false;
        for (int i = 0; i < pair_count - 1; i++)
        {
            if (preferences[pairs[i].winner][pairs[i].loser] <
                preferences[pairs[i + 1].winner][pairs[i + 1].loser])
            {
                // exchanges the (i+1)th pos with ith pos
                swapped = true;
                extra = pairs[i];
                pairs[i] = pairs[i + 1];
                pairs[i + 1] = extra;
            }
        }

        // if there has no exchange happened in the whole above loop
        // then the pairs are sorted
        if (!swapped)
        {
            break;
        }
    }
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        if (!is_cycle(pairs[i].winner, pairs[i].loser))
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }
    return;
}

bool is_cycle(int winner, int loser)
{
    for (int i = 0; i < pair_count; i++)
    {
        // if our loser is the winner of some other pair
        if (loser == pairs[i].winner)
        {
            // also the other pair must be locked
            if (locked[pairs[i].winner][pairs[i].loser])
            {
                // then if the loser of the other pair is our req winner
                // there is a cycle
                if (pairs[i].loser == winner)
                {
                    return true;
                }

                // otherwise check, if the loser of the other pair creates a cycle
                if (is_cycle(winner, pairs[i].loser))
                {
                    return true;
                }
            }
        }
    }

    // after checking through all the pairs through the above loop
    // if there is no such cycle found:
    return false;
}

bool won;

// Print the winner of the election
void print_winner(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        won = true;
        for (int j = 0; j < candidate_count; j++)
        {
            // finding a candidate 'i' which is not the loser to any other candidate 'j'
            if (locked[j][i] == true)
            {
                won = false;
                break;
            }
        }

        // after checking 'i' with ALL other candidates using above loop
        if (won == true)
        {
            printf("%s\n", candidates[i]);
            return;
        }
    }
    return;
}


