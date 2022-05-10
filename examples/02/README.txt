사용하는 방법입니다!
[우분투 기준] 파이썬을 다운로드해줍니다.

apt-get update
apt-get install sudo
sudo apt-get install python3 아니면 apt-get install python3

파이썬 다운로드가 완료되었으면 (gcc는 설치되어있다는 가정하에)
test generator를 실행시켜줍니다.

python3 generator.py <유닛함수 파일> <테스트케이스 파일>
예시) python3 generator.py triangle.c triangle_test_cases.txt

그러면 run_test.sh가 생성될텐데, 이 스크립트를 실행시키면 테스트가 시작됩니다.
예시) sh ./run_test.sh

감사합니다!