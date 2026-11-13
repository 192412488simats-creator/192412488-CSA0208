/* Q7 - Student council election vote counting.
   Counts valid/invalid votes, ranks candidates, identifies winner and ties. */
#include <stdio.h>

#define MAX_CANDIDATES 12
#define MAX_VOTES 5000

typedef struct {
    int candidate;
    int votes;
} Result;

int main(void) {
    int candidates, totalVotes;
    int votes[MAX_VOTES];
    int count[MAX_CANDIDATES + 1] = {0};
    int valid = 0, invalid = 0;

    printf("Enter number of candidates (1-%d): ", MAX_CANDIDATES);
    if (scanf("%d", &candidates) != 1 || candidates < 1 || candidates > MAX_CANDIDATES) {
        printf("Invalid candidate count.\\n");
        return 1;
    }
    printf("Enter number of votes (0-%d): ", MAX_VOTES);
    if (scanf("%d", &totalVotes) != 1 || totalVotes < 0 || totalVotes > MAX_VOTES) {
        printf("Invalid vote count.\\n");
        return 1;
    }
    printf("Enter candidate numbers for each vote:\\n");
    for (int i = 0; i < totalVotes; i++) {
        if (scanf("%d", &votes[i]) != 1) {
            printf("Invalid input.\\n");
            return 1;
        }
        if (votes[i] >= 1 && votes[i] <= candidates) {
            count[votes[i]]++;
            valid++;
        } else invalid++;
    }

    Result results[MAX_CANDIDATES];
    for (int i = 0; i < candidates; i++) {
        results[i].candidate = i + 1;
        results[i].votes = count[i + 1];
    }
    /* Selection sort by descending vote count; candidate number breaks ties. */
    for (int i = 0; i < candidates - 1; i++) {
        int best = i;
        for (int j = i + 1; j < candidates; j++)
            if (results[j].votes > results[best].votes ||
                (results[j].votes == results[best].votes &&
                 results[j].candidate < results[best].candidate))
                best = j;
        if (best != i) {
            Result t = results[i]; results[i] = results[best]; results[best] = t;
        }
    }

    printf("\\nValid votes: %d\\nInvalid votes: %d\\n", valid, invalid);
    printf("Candidate ranking (descending):\\n");
    for (int i = 0; i < candidates; i++)
        printf("Candidate %d: %d votes\\n", results[i].candidate, results[i].votes);

    if (results[0].votes == 0) {
        printf("No valid votes; there is no winner.\\n");
    } else {
        int tie = 0;
        for (int i = 1; i < candidates; i++)
            if (results[i].votes == results[0].votes) tie = 1;
        if (tie) printf("Tie for first place with %d votes.\\n", results[0].votes);
        else printf("Winner: Candidate %d with %d votes.\\n",
                    results[0].candidate, results[0].votes);
    }
    return 0;
}
