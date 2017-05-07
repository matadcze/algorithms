public class Lazy {

	public static void main(String[] args) {
		int[] arry = {2,3,2,1,35,534,3,32,6,5};
		
		for (int i = 0; i < arry.length; i++) {
			System.out.println(arry[i]);
		}
		
		lazy_sort(arry);
		
		for (int i = 0; i < arry.length; i++) {
			System.out.println(arry[i]);
		}

	}

	private static void lazy_sort(int[] arry) {
		for (int i = 0; i < arry.length(); i++) {
			for (int j = 0; j < arry.length(); j++) {
				if(arry[i] < arry[j]){
					swap(arry, i, j);
				}
			}
		}
	}

	private static void swap(int[] arry, int i, int j) {
		int tmp;
		tmp = arry[i];
		arry[i] = arry[j];
		arry[j] = tmp;
	}

}
