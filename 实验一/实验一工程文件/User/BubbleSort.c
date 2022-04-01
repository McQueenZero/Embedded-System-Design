void BubbleSort(int *data, int size)					
//功能仅为冒泡排序的函数
//输入为两变量，分别为指针数组和数组大小
{
	int i, j, tmp;
	for(i = 0; i < size - 1;i++){
		for(j = 0;j < size - i - 1; j++){
			if(data[j] > data[j+1]){	
				tmp = data[j];
				data[j] = data[j+1];
				data[j+1] = tmp;
				/*比较相邻两元素的值，若前者＞后者，
				将前后者交换位置，达到最大的往后“浮”，
				最小的向前“沉”的目的*/
			}
		}
	}
}
void BubbleSortNote(int *data, int *pos, int size)
//冒泡排序，同时记录排序后数组在原数组位置的函数
{
	int i, j, tmp;
	for(i = 0; i < size - 1;i++){
		for(j = 0;j < size - i - 1; j++){
			if(data[j] > data[j+1]){	
				tmp = data[j];
				data[j] = data[j+1];
				data[j+1] = tmp;
				//冒泡排序
				tmp = pos[j];
				pos[j] = pos[j+1];
				pos[j+1] = tmp;
				/*原数组和初始位置数组一一对应。
				（即使相同数值，原始位置也不同）
				例：data[3] = data[9];
				但原始pos[3] = 3, pos[9] = 9；
				即可区分不同位置的相同数
				（main函数中生成初始位置数组pos）
				排序的同时对位置数组进行同样的元素交换，
				输出顺序和排序后数组一致，
				从而得到排序完成后对应数在原数组中的位置*/
			}
		}
	}
}
