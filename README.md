# r2sh-book

### 2022년 전공기초프로젝트2 A03팀의 도서관리 시스템 입니다

## Build
root 계정에서는 실행 되지 않습니다.

```bash
~ $  cd ~ 
~ $  git clone https://github.com/KwonSunJae/r2sh-book.git
~ $  cd r2sh-book 
~/r2sh-book$  chmod +x init.sh 
~/r2sh-book$  source init.sh
```

## 작동환경
ubuntu 20.04.01 LTS  <권장>


ubuntu 18.04.01 LTS  <비권장 - 실행 확인 완료>


ubuntu 22.04.01 LTS  <비권장 - 실행 확인 완료>



## 작동방법

```
$ show  <book-id> : show detail for the book // 해당 책의 상세정보를 보여줍니다
$ search  <keyword> : serach book by keyword and show list // 키워드를 사용하여 책을 검색합니다 , 키워드가 들어있는 책들의 리스트를 보여줍니다
$ loan <user-id> <book-id> : borrow book by bid // 유저 아이디와 책 아이디를 입력하여 책을 대출합니다
$ return <book-id> : return book by bid // 책 아이디를 입력하여 책을 반납합니다
$ info <user-id> : show list of books borrowed by the user // 유저 아이디를 이용하여 빌린 책의 리스트를 보여줍니다
$ auth <username> : generate unique user-id according to username // 유저를 생성합니다 
$ help : show available command list // 사용 가능한 명령어 리스트를 보여줍니다
```
