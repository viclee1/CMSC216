#include <stdio.h>
#include <math.h>
#define SIZE 50

/* Name: Victor Lee, UID: 117213218, Directory ID: vlee842 */

/* checks and returns the weight of assignemnts up to the size */
int check_weights(int a[], int size){
  int i, sum = 0;
  for(i = 0; i < size; i++){
    sum += a[i];
  }
  return sum;
}

/* computes mean of array of ints passed to it, compute up to the size provided */
double compute_mean(int a[], int size){
  int i, sum = 0;
  double mean = 0;
  for(i = 0; i < size; i++) {
    sum += a[i];
  }
  mean = sum / size;
  return mean;
}
/* computes standard deviation of an array of ints passed to it, computing up to size */
double compute_std_dev(int a[], int size){
  int i = 0;
  double sum_part = 0, mean = compute_mean(a, size), square_root = 0,
	 divide_part = 0;
  for(i = 0; i < size; i++){
    sum_part += ((a[i] - mean) * (a[i] - mean));
  }
  divide_part = sum_part / size;
  square_root = sqrt(divide_part);
  return square_root;
}

int main(){
	int penalty = 0, asn_drop = 0, num_asns = 0, i, 
		calc_sum = 0, total_weight = 0;

	int asn_num[SIZE], asn_scores[SIZE], weight[SIZE], days_late[SIZE], 
		penalty_scores[SIZE], drop_grade[SIZE], weighted_scores[SIZE];
 
	double std_dev = 0, mean = 0, num_score = 0; 
	char stat_gen = 'N';
	scanf(" %d %d %c", &penalty, &asn_drop, &stat_gen); 
	scanf(" %d", &num_asns); 
	for(i = 0; i < num_asns; i++){ 
		/* temp values are used to "sort" the array */ 
	        int temp_num, temp_score, temp_weight, temp_late; 
	        scanf("  %d, %d, %d, %d", &temp_num, &temp_score, &temp_weight, &temp_late); 
	        asn_num[temp_num - 1] = temp_num; 
	        asn_scores[temp_num - 1] = temp_score;       
	        weight[temp_num - 1] = temp_weight; 
	        days_late[temp_num - 1] = temp_late; 
	} 
	 
	/* if weights do not equal 100 when summed together, the program is terminated */ 
	if(check_weights(weight, num_asns) != 100){ 
		printf("ERROR: Invalid values provided \n"); 
	        return 0; 
	}  
	 
	/* applies penalized scores to the original scores if there is a penalty */ 
	if(penalty != 0){ 
	        for(i = 0; i < num_asns; i++){ 
			penalty_scores[i] = asn_scores[i] - (penalty * days_late[i]); 
	                /* prevents scores from being less than 0 */ 
	                if(penalty_scores[i] < 0){ 
	                	penalty_scores[i] = 0; 
	                }               
	        }  
	} 

	if(stat_gen == 'y' || stat_gen == 'Y'){ 
	        if(penalty != 0){ 
	                mean = compute_mean(penalty_scores, num_asns); 
	                std_dev = compute_std_dev(penalty_scores, num_asns); 
	        } else { 
	                mean = compute_mean(asn_scores, num_asns); 
	                std_dev = compute_std_dev(asn_scores, num_asns); 
	        } 
	} 
	 
	/* drop assignments */ 

	if(asn_drop != 0){  
		int marker = -1, cnt, small_size;
                for(i = 0; i < num_asns; i++){  
                	drop_grade[i] = 0;  
	                weighted_scores[i] = asn_scores[i] * weight[i];  
	        }  

	        for(cnt = 0; cnt < asn_drop; cnt++){  
	        	/* a grade 100 with weight 100 is only 10000, and this is the largest amount */  
	                small_size = 10001;  
	                for(i = 0; i < num_asns; i++){  
				/* checks for smallest value and if it has already been chosen yet to be dropped */
	                	if(drop_grade[i] != -1 &&  weighted_scores[i] < small_size){ 
					marker = i; 
	                                small_size = weighted_scores[i];  
	                        }   
	                }   
			/* used to skip over dropped grades when calculating numeric score */
	                drop_grade[marker] = -1;
	        }
	}
	
	/*  calculates numeric score */
	if(penalty != 0) {
		for(i = 0; i < num_asns; i++){
			if(drop_grade[i] != -1){
				calc_sum += (penalty_scores[i] * weight[i]);
				total_weight += weight[i];
			}
		}
		num_score = (double) calc_sum/total_weight;
	} else { 
	       for(i = 0; i < num_asns; i++){
			if(drop_grade[i] != -1){
				calc_sum += weighted_scores[i];
				total_weight += weight[i];
			}
		}
		num_score = (double) calc_sum/total_weight;
	}
	 
	printf("Numeric Score: %5.4f\n", num_score); 
	printf("Points Penalty Per Day Late: %d\n", penalty); 
	printf("Number of Assignments Dropped: %d\n", asn_drop); 
	printf("Values Provided:\n"); 
	printf("Assignment, Score, Weight, Days Late\n"); 
	 
	for(i = 0; i < num_asns; i++){ 
		printf("%d, %d, %d, %d\n", asn_num[i], asn_scores[i], weight[i], days_late[i]); 
	} 
	 
	if(stat_gen == 'y' || stat_gen == 'Y'){ 
		printf("Mean: %5.4f, Standard Deviation: %5.4f\n", mean, std_dev); 
	} 
	return 0; 
}    
