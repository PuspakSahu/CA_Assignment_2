// Create other necessary functions here


__global__ void cudaCMM(int *matA, int *matB, int *output, int N, int num_thread)
{
 
   for(int rowA=threadIdx.x;rowA<N;rowA+=num_thread){

		
			for(int colB = 0; colB < N; colB += 2){
				int s = 0;

				for(int iter = 0; iter < N; iter++) 
				{
					s += matA[rowA * N + iter] * matB[iter * N + colB];
					
				}
				output[rowA>>1 * (N>>1) +colB>>1]+=s;
			
			for(int colB = 1; colB < N; colB += 2){
				int s = 0;

				for(int iter = 0; iter < N; iter++) 
				{
					s += matA[rowA * N + iter] * matB[iter * N + colB];
					
				}
				output[rowA>>1 * (N>>1) +colB>>1]+=s;
				}
	}
	}
}


		














    //     if(rowA &1){
    //     	//odd row
        	
    //     	for(int i=0;i<N;i++){
    //     		//traverse over all elements in the row
        		
    //     		if(!(i&1)){
    //     			//even element
    //     			int rowB = i+1;
    //     			for(int k=0,si=0;k<N;k+=2,si++)
    //     				sum[si] += matA[rowA*N +i] * matB[rowB*N +k];
    //     		}
    //     		else{ 
    //     			//odd element
    //     			int rowB = i-1;
    //     			for(int k=1,si=0;k<N;k+=2,si++){
    //     				sum[si] += matA[rowA*N +i] * matB[rowB*N +k];
    //     			}
    //     		}
    //     	}
        	
    //     }
    //     else{
    //    		//even row
       		
    //    		for(int i=0;i<N;i++){
    //     		//traverse over all elements in the row
        		
    //     		if(!(i&1)){
    //     			//even element
    //     			int rowB = i+1;
    //     			for(int k=1,si=0;k<N;k+=2,si++)
    //     				sum[si] += matA[rowA*N +i] * matB[rowB*N +k];
    //     		}
    //     		else{
    //     			//odd element
    //     			int rowB = i-1;
    //     			for(int k=0,si=0;k<N;k+=2,si++){
    //     				sum[si] += matA[rowA*N +i] * matB[rowB*N +k];
    //     			}
    //     		}
    //     	}
    //     }

    //   int indexC = rowA*N/2;
    //   for(int si=0;si<N/2;si++){
    // 	  output[indexC + si] = sum[si];
    //   }

    // }

}

// Fill in this function
void gpuThread(int N, int *matA, int *matB, int *output)
{   
    int num_block = 1;
    int num_thread = N;
    int *d_matA, *d_matB, *d_out;

    // allocate device memory 
    cudaMalloc((void**)&d_matA, sizeof(int)*N*N);
    cudaMalloc((void**)&d_matB, sizeof(int)*N*N);
    cudaMalloc((void**)&d_out, sizeof(int)*N*N/4);

    // copy data from host to to device
    cudaMemcpy(d_matA, matA, sizeof(int)*N*N, cudaMemcpyHostToDevice);
    cudaMemcpy(d_matB, matB, sizeof(int)*N*N, cudaMemcpyHostToDevice);


    //function call for CMM
    cudaCMM<<<num_block, num_thread>>>(d_matA, d_matB, d_out, N, num_thread);

    // copy data from device to host 
    cudaMemcpy(output,d_out, sizeof(int)*N*N/4,cudaMemcpyDeviceToHost);

   

    // #free GPU side memory 
    cudaFree(d_matA);
    cudaFree(d_matB);
    cudaFree(d_out);

}




