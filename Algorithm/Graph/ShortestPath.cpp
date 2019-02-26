const int maxn(1e4+7);
const int INF(0x3f3f3f3f);
int n;

//Dijkstra
int mapp[maxn][maxn], lenth[maxn];
bool visited[maxn];
void dijkstra(int nowPos) {
	mem(visited, 0);
	mem(lenth, 0x3f);
	visited[nowPos] = 1;
	lenth[nowPos] = 0;
	per(i,1,n) {
		per(j, 1, n+1) {
			if (mapp[nowPos][j] + lenth[nowPos] < lenth[j]) {
				lenth[j] = mapp[nowPos][j] + lenth[nowPos];
			}
		}
		int minPos = nowPos, minn = INF;
		per(j, 1, n+1) {
			if (!visited[j] && lenth[j] < minn) {
				minn = lenth[j];
				minPos = j;
			}
		}
		nowPos = minPos;
		visited[nowPos] = 1;
		if (nowPos == n) {
			break;
		}
	}
}


//Floyd
void Floyd() {
	int i,j,k;
	for(k=0;k<Point;k++) {
		for(i=0;i<Point;i++) {
			for(j=0;j<Point;j++) {
				if(Far[i][j]>Far[i][k]+Far[k][j]) {
					Far[i][j] = Far[i][k]+Far[k][j];
				}
			}
		}
	}
}


//SPFA
struct queue {
    int head,tail;
    int capacity;
    int empty;
    int full;
    int queue[MAXPOINT+1];
};

typedef struct queue Queue;

Queue Q;

void Queue_init() {
    Q.head = Q.tail = 0;
    Q.capacity = MAXPOINT+1;
    Q.empty = 1;
    Q.full = 0;
    memset(Q.queue, -1, sizeof(Q.queue));
}

void Queue_enque(int dex) {
    Q.queue[Q.tail] = dex;
    if(Q.tail+1 == Q.capacity) {
        Q.tail = 0;
    } else {
        Q.tail++;
    }
    Q.empty = 0;
    if(Q.tail+1 == Q.head) {
        Q.full = 1;
    }
}

int Queue_deque() {
    int n = Q.queue[Q.head];
    if(Q.head+1 == Q.capacity) {
        Q.head = 0;
    } else {
        Q.head++;
    }
    if(Q.head == Q.tail) {
        Q.empty = 1;
    }
    return n;
}

void SPFA(int start) {
    //初始化
    Datatype lenth[MAXPOINT];
    Queue_init();
    memset(lenth, 0x3f, sizeof(lenth));
    lenth[start] = 0;
    Queue_enque(start);
    //队列操作
    int v;
    while(Q.empty==0) {
        v = Queue_deque();
        for(int i=0;i<Point;i++) {
            if(Far[v][i]+lenth[v]<lenth[i]) {
                lenth[i] = Far[v][i]+lenth[v];
                Queue_enque(i);
            }
        }
    }
}


