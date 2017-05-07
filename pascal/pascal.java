class PascalTriangle {
	public static void main(String[] args) {
		final int size = 20;
		int[][] arry = new int[size][size];

		for (int i = 0; i < size; i++) {
			arry[i][0] = 1;
			arry[i][i] = 1;
		}
		
		for (int i = 2; i < size; i++) {
			for (int j = 1; j < size; j++) {
				arry[i][j] = arry[i-1][j-1] + arry[i-1][j];
			}
		}

		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				System.out.print(arry[i][j] + " ");
				
			}
			System.out.println("");
		}
	}

}
