# 2019-Programs
## pixy2 get color info library

####class : pixy2_info

####functions
　
　void set offsset(offset x, offset y) : 全方位ミラーの中心座標を、オフセットとして設定する。
  void attach sig num(int orange sig, int yellow sig, int blue sig) : pixyからの返り値と色を対応させるため色ごとに数値ラベルを設定する。  デフォルト値 orange:1 yellow:2 blue:3
  
  int {$color} angle() : 実際の角度を100倍にしている。範囲は -314〜314　
  int {$color} x() : Pixyからの、物体の座標のx成分。範囲は設定してるオフセットによって変わる。
  int {$color} y() : Pixyからの、物体の座標のy成分。範囲は設定してるオフセットによって変わる。

  int {$color} dist() : ロボットと物体との距離を近似する関数。現在はコメントアウトされており、実装されていない。

  $color = orange | yellow | blue
