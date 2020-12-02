# 1.ロボットシステム学課題1について
第7回と8回で作成したデバイスドライバーをベースに、オリジナリティーある改造をして、<br>
GitHubに置くこと。

# 2.使用した道具について
・ラズベリーパイ4 ×1 <br>
・赤色LED ×1 <br>
・緑色LED ×1 <br>
・ブレッドボード ×1 <br>
・ジャンパー線オスメス ×4 <br>
・抵抗300Ω ×2 

# 3.デバイスドライバーの改造について
第7回と8回の講義動画で、上田先生が一から作成したLEDを1個をon/offで光らせるデバイスドライバーの<br>
プログラムをベースにして、赤色と緑色の2つのLEDをon/offで同時に光らせたり、それぞれのLEDを光らせ<br>
たり、同時に消したりする動作を行うデバイスドライバーを作成しました。

# 4.回路の配線について
以下のような回路を作成しました。<br>
![画像名](https://github.com/okasyu/test/blob/main/%E5%86%99%E7%9C%9F2.jpg)

# 5.デバイスドライバーを動かす手順について 
デバイスドライバーを動かす手順は以下の通りになる。<br>
1. git clone https://github.com/okasyu/make_device-driver.git  <br>
2. cd make_device-driver/ <br> 
3. cd myled.c(LED1個についてのデバイスドライバーを動かすプログラムを作成し、その後に自分で改造を行う。)<br>
4. make <br>
5. sudo insmod myled.ko <br>
6. sudo chmod 666 /dev/myled0 <br>
7. echo 2 > /dev/myled0, echo 3 > /dev/myled0, echo 0 > /dev/myled0, echo 1 > /dev/myled0の <br>
   いずれかのコマンドを実行して、LEDを光らせたり消したりする。
  
# 6.デバイスドライバーを実際に動かしている動画について
こちらのURLからアクセスする。

URL　https://www.youtube.com/watch?v=WahY1PdwhqA　
 





