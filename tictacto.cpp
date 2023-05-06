#include <iostream>
using namespace std;

class hBoard{
private:
    char board[3][3];

public:
    hBoard() {
        // 게임 보드 초기화
        for(int row=0; row<3; row++) {
            for(int col=0; col<3; col++) {
                board[row][col] = '-';
            }
        }
    }

    void drawBoard() {
        cout << "---------" << endl;
        for(int row=0; row<3; row++) {
            cout << "| ";
            for(int col=0; col<3; col++) {
                cout << board[row][col] << " | ";
            }
            cout << endl << "---------" << endl;
        }
    }

    void updateBoard(int row, int col) {
        board[row][col] = 'X'; // 사용자가 말을 둔 위치를 X로 업데이트
    }

    void getInput() {
        int row, col;
        cout << "Enter row and column (0-2): ";
        cin >> row >> col;
        updateBoard(row, col); // 입력 받은 위치를 게임 보드에 업데이트
    }
};


class GameAlgorithm {
private:
    char board[3][3];

public:
  int weight[3][3] = { {3,2,3},{2,4,2},{3,2,3} }; // 위치 별 가중치
  int max_weight = -1; // 가중치의 최댓값을 저장할 변수
  int max_weight_row = -1; // 가중치의 최댓값이 위치한 행의 인덱스를 저장할 변수
  int max_weight_col = -1; // 가중치의 최댓값이 위치한 열의 인덱스를 저장할 변수

  void initBoard(int board[3][3]) {
    for (int row = 0; row < 3; ++row) {
      for (int col = 0; col < 3; ++col) {
        board[row][col] = 0; // 모든 위치를 비어있는 상태로 초기화
      }
    }
  }

  bool v_put(int board[3][3], int row, int col) {
    if (row < 0 || row > 2 || col < 0 || col > 2) { // 범위를 벗어난 경우
      return false;
    }
    if (board[row][col] != 0) { // 이미 말이 놓여져 있는 경우
      return false;
    }
    return true;
  }

  void put(int board[3][3], int row, int col, int player) {
    board[row][col] = player; // 해당 위치에 플레이어의 말을 놓음
  }

  bool gameover() {
  // 비어있는 위치가 없으면 게임이 끝난 것으로 판단합니다.
  for (int row = 0; row < 3; ++row) {
    for (int col = 0; col < 3; ++col) {
      if (board[row][col] == 0) {
        return false;
      }
    }
  }

  // 가로 방향으로 세 개의 말이 같은 경우가 있는지 확인합니다.
  for (int row = 0; row < 3; ++row) {
    if (board[row][0] == board[row][1] && board[row][1] == board[row][2] && board[row][0] != 0) {
      return true;
    }
  }

  // 세로 방향으로 세 개의 말이 같은 경우가 있는지 확인합니다.
  for (int col = 0; col < 3; ++col) {
    if (board[0][col] == board[1][col] && board[1][col] == board[2][col] && board[0][col] != 0) {
      return true;
    }
  }

  // 대각선 방향으로 세 개의 말이 같은 경우가 있는지 확인합니다.
  if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != 0) {
    return true;
  }
  if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != 0) {
    return true;
  }

  // 게임이 끝나지 않았다면 false를 반환합니다.
  return false;
}


bool is_move_possible(int row, int col) {
    if (row < 0 || row >= 3) return false;
    if (col < 0 || col >= 3) return false;
    if (board[row][col] != '-') return false;
    return true;
}

int winner() {
  // 첫 번째 플레이어가 이긴 경우
  if (board[0][0] == 1 && board[0][1] == 1 && board[0][2] == 1) return 1;
  if (board[1][0] == 1 && board[1][1] == 1 && board[1][2] == 1) return 1;
  if (board[2][0] == 1 && board[2][1] == 1 && board[2][2] == 1) return 1;
  if (board[0][0] == 1 && board[1][0] == 1 && board[2][0] == 1) return 1;
  if (board[0][1] == 1 && board[1][1] == 1 && board[2][1] == 1) return 1;
  if (board[0][2] == 1 && board[1][2] == 1 && board[2][2] == 1) return 1;
  if (board[0][0] == 1 && board[1][1] == 1 && board[2][2] == 1) return 1;
  if (board[0][2] == 1 && board[1][1] == 1 && board[2][0] == 1) return 1;

  // 두 번째 플레이어가 이긴 경우
  if (board[0][0] == 2 && board[0][1] == 2 && board[0][2] == 2) return 2;
  if (board[1][0] == 2 && board[1][1] == 2 && board[1][2] == 2) return 2;
  if (board[2][0] == 2 && board[2][1] == 2 && board[2][2] == 2) return 2;
  if (board[0][0] == 2 && board[1][0] == 2 && board[2][0] == 2) return 2;
  if (board[0][1] == 2 && board[1][1] == 2 && board[2][1] == 2) return 2;
  if (board[0][2] == 2 && board[1][2] == 2 && board[2][2] == 2) return 2;
  if (board[0][0] == 2 && board[1][1] == 2 && board[2][2] == 2) return 2;
  if (board[0][2] == 2 && board[1][1] == 2 && board[2][0] == 2) return 2;

  // 비긴 경우
  if (!is_move_possible(row,col)) return 0;

  // 게임이 아직 끝나지 않았음
  return -1;
}

void make_move(int row, int col, int player) {
  board[row][col] = player;
}


int com_put() {
   srand((unsigned int)time(NULL)); // srand 함수를 이용해 컴퓨터가 매번 같은 위치에 놓을 경우를 방지=

  int max_weight = -1; // 가중치의 최댓값을 저장할 변수
  int max_weight_row = -1; // 가중치의 최댓값이 위치한 행의 인덱스를 저장할 변수
  int max_weight_col = -1; // 가중치의 최댓값이 위치한 열의 인덱스를 저장할 변수

  // 말을 둘 수 있는 위치 중에서 가중치의 최댓값을 찾습니다.
  for (int row = 0; row < 3; ++row) {
    for (int col = 0; col < 3; ++col) {
      if (board[row][col] == 0) { // 해당 위치가 비어있는 경우에만 가중치를 계산
        if (weight[row][col] > max_weight) {
          max_weight = weight[row][col];
          max_weight_row = row;
          max_weight_col = col;
        } } } }  // 가중치의 최댓값이 위치한 위치에 말을 놓습니다.
  make_move(max_weight_row, max_weight_col, 2);
  return 0;
}

};


class input {
  private:
    int board[3][3] = { {0, 0, 0}, {0, 0, 0}, {0, 0, 0} };
  public:
    int get_put() {
      int row, col;
      cout << "행과 열의 위치를 입력하세요: ";
      cin >> row >> col;
      return (row * 3 + col);
    }
  
    bool vali_put(int row, int col) {
      if (row < 0 || row > 2 || col < 0 || col > 2) return false;
      if (board[row][col] != 0) return false;
      return true;
    }
  
    void print_board() {
      cout << "-----------" << endl;
      for (int row = 0; row < 3; ++row) {
        cout << "|";
        for (int col = 0; col < 3; ++col) {
          if (board[row][col] == 0) cout << "   |";
          else if (board[row][col] == 1) cout << " O |";
          else cout << " X |";
        }
        cout << endl << "-----------" << endl;
      }
    }
};

int main() {
    hBoard board; // 게임 보드 객체 생성
    GameAlgorithm algorithm; // 게임 알고리즘 객체 생성

    int player = 1; // 플레이어 1부터 시작
    while(!algorithm.gameover()) { // 게임이 끝나지 않은 경우 반복
        board.drawBoard(); // 현재 게임 보드 출력

        // 플레이어 1인 경우 사용자에게 입력 받음
        if (player == 1) {
            cout << "Player " << player << " (X) turn." << endl;
            board.getInput();
        }
        // 플레이어 2인 경우 게임 알고리즘으로부터 위치를 받아서 게임 보드에 업데이트
        else {
            algorithm.updateBoard(board); // 게임 알고리즘에 현재 게임 보드 정보 전달
            cout << "Player " << player << " (O) turn." << endl;
            cout << "Computer plays at " << algorithm.max_weight_row << ", " << algorithm.max_weight_col << endl;
            board.updateBoard(algorithm.max_weight_row, algorithm.max_weight_col); // 알고리즘이 선택한 위치에 말 놓기
        }

        // 다음 플레이어의 차례로 넘어가기
        player = (player == 1) ? 2 : 1;

        // 게임이 끝난 경우 승자 출력
        if (algorithm.gameover()) {
            board.drawBoard();
            int winner = algorithm.winner();
            if (winner == 1) {
                cout << "Player 1 (X) wins!" << endl;
            } else if (winner == 2) {
                cout << "Player 2 (O) wins!" << endl;
            } else {
                cout << "It's a tie!" << endl;
            }
        }
    }

    return 0;
}

