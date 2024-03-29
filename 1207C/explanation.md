# Gas Pipeline 题解

## 题意分析

你要在一个区域修建煤气管道，煤气管道由两部分组成，支架与管道。某些区间有道路垂直于管道穿过，这些部分你需要提高一倍的支架的高度以保证管道和来回车辆不会冲突。提高支架的部分需要用Z型管道来衔接，Z型管道的使用长度是一般管道的两倍，价格也是两倍，降低支架的部分也是如此。**而且目前你无法预先知道是管道更贵还是支架更贵**

## 思路

这道题的关键是最后一句，我们无法提前知道是管道更贵还是支架更贵，如果单位长度的管道价格等于单位长度的支架价格的10000倍，那么我们要尽量少用Z型管道，即使浪费部分支架。相反亦此。因此我们可以使用动态规划+区分情况来做，总体思路如下:

假设我们要建设第i个支架

- 建设第i个高支架的费用可能是以下两种来源中的较低值
    - 建设i-1个高支架的费用 + 管道的单价 + 支架单价 * 2
    - 建设i-1个低支架的费用 + 管道的单价 * 2 + 支架单价 * 2
- 建设第i个低支架的费用可能是以下两种来源中的较低值
    - 建设i-1个高支架的费用 + 管道的单价 * 2 + 支架单价
    - 建设i-1个低支架的费用 + 管道的单价 + 支架单价

还有部分情况我们必须设置高支架

- 前方有道路横穿
- 后方有道路横穿

部分情况我们必须使用低支架

- 起始位置
- 结束位置