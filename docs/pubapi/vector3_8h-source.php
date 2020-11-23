<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<html><head><meta http-equiv="Content-Type" content="text/html;charset=iso-8859-1">
<title>vector3.h Source File</title>
<link href="doxygen.css" rel="stylesheet" type="text/css">
</head><body>
<!-- Generated by Doxygen 1.3-rc2 -->
<center>
<a class="qindex" href="index.php">Main Page</a> &nbsp; <a class="qindex" href="modules.php">Modules</a> &nbsp; <a class="qindex" href="hierarchy.php">Class Hierarchy</a> &nbsp; <a class="qindex" href="classes.php">Alphabetical List</a> &nbsp; <a class="qindex" href="annotated.php">Compound List</a> &nbsp; <a class="qindex" href="files.php">File List</a> &nbsp; <a class="qindex" href="functions.php">Compound Members</a> &nbsp; </center>
<hr><h1>vector3.h</h1><div class="fragment"><pre>00001 <span class="comment">/*</span>
00002 <span class="comment"> *  AE Engine</span>
00003 <span class="comment"> *</span>
00004 <span class="comment"> *  Copyright (C) 2003 Riku "Rakkis" Nurminen</span>
00005 <span class="comment"> *</span>
00006 <span class="comment"> *  This program is free software; you can redistribute it and/or modify</span>
00007 <span class="comment"> *  it under the terms of the GNU General Public License as published by</span>
00008 <span class="comment"> *  the Free Software Foundation; either version 2 of the License, or</span>
00009 <span class="comment"> *  (at your option) any later version.</span>
00010 <span class="comment"> *</span>
00011 <span class="comment"> *  This program is distributed in the hope that it will be useful,</span>
00012 <span class="comment"> *  but WITHOUT ANY WARRANTY; without even the implied warranty of</span>
00013 <span class="comment"> *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the</span>
00014 <span class="comment"> *  GNU General Public License for more details.</span>
00015 <span class="comment"> *</span>
00016 <span class="comment"> *  You should have received a copy of the GNU General Public License</span>
00017 <span class="comment"> *  along with this program; if not, write to the Free Software</span>
00018 <span class="comment"> *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA</span>
00019 <span class="comment"> *</span>
00020 <span class="comment"> */</span>
00021 
00022 <span class="preprocessor">#ifndef __AELIB_AEGEOM_VECTOR3_H__</span>
00023 <span class="preprocessor"></span><span class="preprocessor">#define __AELIB_AEGEOM_VECTOR3_H__</span>
00024 <span class="preprocessor"></span>
00025 <span class="preprocessor">#define ONLY_INCLUDE_STD</span>
00026 <span class="preprocessor"></span><span class="preprocessor">#include &lt;aedefs.h&gt;</span>
00027 <span class="preprocessor">#undef ONLY_INCLUDE_STD</span>
00028 <span class="preprocessor"></span>
<a name="l00033"></a><a class="code" href="classaeVector3.php">00033</a> <span class="keyword">class </span><a class="code" href="classaeVector3.php">aeVector3</a> {
00034         AECF_CNDEF
00035 
00036  <span class="keyword">public</span>:
00041         <a class="code" href="classaeVector3.php#a0">aeVector3</a>();
00042 
<a name="l00050"></a><a class="code" href="classaeVector3.php#a1">00050</a>         <a class="code" href="classaeVector3.php#a0">aeVector3</a>(<span class="keywordtype">float</span> nx, <span class="keywordtype">float</span> ny, <span class="keywordtype">float</span> nz = 0) : <a class="code" href="classaeVector3.php#m0">x</a>(nx), <a class="code" href="classaeVector3.php#m1">y</a>(ny), <a class="code" href="classaeVector3.php#m2">z</a>(nz) {}
00051 
<a name="l00057"></a><a class="code" href="classaeVector3.php#a2">00057</a>         <a class="code" href="classaeVector3.php#a0">aeVector3</a>(<span class="keyword">const</span> <a class="code" href="classaeVector3.php">aeVector3</a> &amp;v) : <a class="code" href="classaeVector3.php#m0">x</a>(v.<a class="code" href="classaeVector3.php#m0">x</a>), <a class="code" href="classaeVector3.php#m1">y</a>(v.<a class="code" href="classaeVector3.php#m1">y</a>), <a class="code" href="classaeVector3.php#m2">z</a>(v.<a class="code" href="classaeVector3.php#m2">z</a>) {}
00058 
00059         ~<a class="code" href="classaeVector3.php">aeVector3</a>() {};
00060 
<a name="l00062"></a><a class="code" href="classaeVector3.php#m0">00062</a>         <span class="keywordtype">float</span> <a class="code" href="classaeVector3.php#m0">x</a>;
<a name="l00064"></a><a class="code" href="classaeVector3.php#m1">00064</a>         <span class="keywordtype">float</span> <a class="code" href="classaeVector3.php#m1">y</a>;
<a name="l00066"></a><a class="code" href="classaeVector3.php#m2">00066</a>         <span class="keywordtype">float</span> <a class="code" href="classaeVector3.php#m2">z</a>;
00067 
<a name="l00076"></a><a class="code" href="classaeVector3.php#l0">00076</a>         <span class="keyword">inline</span> <span class="keyword">friend</span> <a class="code" href="classaeVector3.php">aeVector3</a> <a class="code" href="classaeVector3.php#a10">operator+</a>(<span class="keyword">const</span> <a class="code" href="classaeVector3.php">aeVector3</a> &amp;v1, <span class="keyword">const</span> <a class="code" href="classaeVector3.php">aeVector3</a> &amp;v2) {
00077                 <span class="keywordflow">return</span> <a class="code" href="classaeVector3.php#a0">aeVector3</a>(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
00078         }
00079 
<a name="l00088"></a><a class="code" href="classaeVector3.php#l1">00088</a>         <span class="keyword">inline</span> <span class="keyword">friend</span> <a class="code" href="classaeVector3.php">aeVector3</a> <a class="code" href="classaeVector3.php#a11">operator-</a>(<span class="keyword">const</span> <a class="code" href="classaeVector3.php">aeVector3</a> &amp;v1, <span class="keyword">const</span> <a class="code" href="classaeVector3.php">aeVector3</a> &amp;v2) {
00089                 <span class="keywordflow">return</span> <a class="code" href="classaeVector3.php#a0">aeVector3</a>(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
00090         }
00091 
<a name="l00100"></a><a class="code" href="classaeVector3.php#l2">00100</a>         <span class="keyword">inline</span> <span class="keyword">friend</span> <span class="keywordtype">float</span> <a class="code" href="classaeVector3.php#l2">operator*</a>(<span class="keyword">const</span> <a class="code" href="classaeVector3.php">aeVector3</a> &amp;v1, <span class="keyword">const</span> <a class="code" href="classaeVector3.php">aeVector3</a> &amp;v2) {
00101                 <span class="keywordflow">return</span> (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);
00102         }
00103 
<a name="l00112"></a><a class="code" href="classaeVector3.php#l3">00112</a>         <span class="keyword">inline</span> <span class="keyword">friend</span> <a class="code" href="classaeVector3.php">aeVector3</a> <a class="code" href="classaeVector3.php#l3">operator%</a>(<span class="keyword">const</span> <a class="code" href="classaeVector3.php">aeVector3</a> &amp;v1, <span class="keyword">const</span> <a class="code" href="classaeVector3.php">aeVector3</a> &amp;v2) {
00113                 <span class="keywordflow">return</span> <a class="code" href="classaeVector3.php#a0">aeVector3</a>((v1.y * v2.z) - (v1.z * v2.y),
00114                                                  (v1.z * v2.x) - (v1.x * v2.z),
00115                                                  (v1.x * v2.y) - (v1.y * v2.x));
00116         }
00117 
<a name="l00126"></a><a class="code" href="classaeVector3.php#l4">00126</a>         <span class="keyword">inline</span> <span class="keyword">friend</span> <a class="code" href="classaeVector3.php">aeVector3</a> <a class="code" href="classaeVector3.php#l2">operator*</a>(<span class="keyword">const</span> <a class="code" href="classaeVector3.php">aeVector3</a> &amp;v1, <span class="keywordtype">float</span> s) {
00127                 <span class="keywordflow">return</span> <a class="code" href="classaeVector3.php#a0">aeVector3</a>(v1.x * s, v1.y * s, v1.z * s);
00128         }
00129 
<a name="l00138"></a><a class="code" href="classaeVector3.php#l5">00138</a>         <span class="keyword">inline</span> <span class="keyword">friend</span> <a class="code" href="classaeVector3.php">aeVector3</a> <a class="code" href="classaeVector3.php#l2">operator*</a>(<span class="keywordtype">float</span> s, <span class="keyword">const</span> <a class="code" href="classaeVector3.php">aeVector3</a> &amp;v1) {
00139                 <span class="keywordflow">return</span> <a class="code" href="classaeVector3.php#a0">aeVector3</a>(v1.x * s, v1.y * s, v1.z * s);
00140         }
00141 
<a name="l00150"></a><a class="code" href="classaeVector3.php#l6">00150</a>         <span class="keyword">inline</span> <span class="keyword">friend</span> <a class="code" href="classaeVector3.php">aeVector3</a> <a class="code" href="classaeVector3.php#l2">operator*</a>(<span class="keywordtype">int</span> s, <span class="keyword">const</span> <a class="code" href="classaeVector3.php">aeVector3</a> &amp;v1) {
00151                 <span class="keywordflow">return</span> v1 * (float)s;
00152         }
00153 
<a name="l00162"></a><a class="code" href="classaeVector3.php#l7">00162</a>         <span class="keyword">inline</span> <span class="keyword">friend</span> <a class="code" href="classaeVector3.php">aeVector3</a> <a class="code" href="classaeVector3.php#l7">operator/</a>(<span class="keyword">const</span> <a class="code" href="classaeVector3.php">aeVector3</a> &amp;v1, <span class="keywordtype">float</span> s) {
00163                 s = 1.0f / s;
00164                 <span class="keywordflow">return</span> <a class="code" href="classaeVector3.php#a0">aeVector3</a>(v1.x * s, v1.y * s, v1.z * s);
00165         }
00166 
<a name="l00175"></a><a class="code" href="classaeVector3.php#l8">00175</a>         <span class="keyword">inline</span> <span class="keyword">friend</span> <a class="code" href="classaeVector3.php">aeVector3</a> <a class="code" href="classaeVector3.php#l7">operator/</a>(<span class="keyword">const</span> <a class="code" href="classaeVector3.php">aeVector3</a> &amp;v1, <span class="keywordtype">int</span> s) {
00176                 <span class="keywordflow">return</span> (v1 / (float)s);
00177         }
00178 
<a name="l00187"></a><a class="code" href="classaeVector3.php#l9">00187</a>         <span class="keyword">inline</span> <span class="keyword">friend</span> <span class="keywordtype">bool</span> <a class="code" href="classaeVector3.php#l9">operator==</a>(<span class="keyword">const</span> <a class="code" href="classaeVector3.php">aeVector3</a> &amp;v1, <span class="keyword">const</span> <a class="code" href="classaeVector3.php">aeVector3</a> &amp;v2) {
00188                 <span class="keywordflow">return</span> v1.x == v2.x &amp;&amp; v1.y == v2.y &amp;&amp; v1.z == v2.z;
00189         }
00190 
<a name="l00199"></a><a class="code" href="classaeVector3.php#l10">00199</a>         <span class="keyword">inline</span> <span class="keyword">friend</span> <span class="keywordtype">bool</span> <a class="code" href="classaeVector3.php#l10">operator!=</a>(<span class="keyword">const</span> <a class="code" href="classaeVector3.php">aeVector3</a> &amp;v1, <span class="keyword">const</span> <a class="code" href="classaeVector3.php">aeVector3</a> &amp;v2) {
00200                 <span class="keywordflow">return</span> v1.x != v2.x || v1.y != v2.y || v1.z != v2.z;
00201         }
00202 
<a name="l00210"></a><a class="code" href="classaeVector3.php#a4">00210</a>         <span class="keyword">inline</span> <span class="keywordtype">float</span> <a class="code" href="classaeVector3.php#a4">operator[]</a>(<span class="keywordtype">int</span> n)<span class="keyword"> const </span>{ <span class="keywordflow">return</span> !n ? x : n &amp; 1 ? y : z; }
00211 
<a name="l00219"></a><a class="code" href="classaeVector3.php#a5">00219</a>         <span class="keyword">inline</span> <span class="keywordtype">float</span> &amp; <a class="code" href="classaeVector3.php#a4">operator[]</a>(<span class="keywordtype">int</span> n) { <span class="keywordflow">return</span> !n ? x : n &amp; 1 ? y : z; }
00220 
<a name="l00228"></a><a class="code" href="classaeVector3.php#a6">00228</a>         <span class="keyword">inline</span> <a class="code" href="classaeVector3.php">aeVector3</a> &amp; <a class="code" href="classaeVector3.php#a6">operator+=</a>(<span class="keyword">const</span> <a class="code" href="classaeVector3.php">aeVector3</a> &amp;v1) {
00229                 x += v1.x;
00230                 y += v1.y;
00231                 z += v1.z;
00232                 <span class="keywordflow">return</span> *<span class="keyword">this</span>;
00233         }
00234 
<a name="l00242"></a><a class="code" href="classaeVector3.php#a7">00242</a>         <span class="keyword">inline</span> <a class="code" href="classaeVector3.php">aeVector3</a> &amp; <a class="code" href="classaeVector3.php#a7">operator-=</a>(<span class="keyword">const</span> <a class="code" href="classaeVector3.php">aeVector3</a> &amp;v1) {
00243                 x -= v1.x;
00244                 y -= v1.y;
00245                 z -= v1.z;
00246                 <span class="keywordflow">return</span> *<span class="keyword">this</span>;
00247         }
00248 
<a name="l00256"></a><a class="code" href="classaeVector3.php#a8">00256</a>         <span class="keyword">inline</span> <a class="code" href="classaeVector3.php">aeVector3</a> &amp; <a class="code" href="classaeVector3.php#a8">operator*=</a>(<span class="keywordtype">float</span> s) {
00257                 x *= s;
00258                 y *= s;
00259                 z *= s;
00260                 <span class="keywordflow">return</span> *<span class="keyword">this</span>;
00261         }
00262 
<a name="l00270"></a><a class="code" href="classaeVector3.php#a9">00270</a>         <span class="keyword">inline</span> <a class="code" href="classaeVector3.php">aeVector3</a> &amp; <a class="code" href="classaeVector3.php#a9">operator/=</a>(<span class="keywordtype">float</span> s) {
00271                 s = 1.0f / s;
00272                 x *= s;
00273                 y *= s;
00274                 z *= s;
00275                 <span class="keywordflow">return</span> *<span class="keyword">this</span>;
00276         }
00277 
<a name="l00284"></a><a class="code" href="classaeVector3.php#a10">00284</a>         <span class="keyword">inline</span> <a class="code" href="classaeVector3.php">aeVector3</a> <a class="code" href="classaeVector3.php#a10">operator+</a>()<span class="keyword"> const </span>{ <span class="keywordflow">return</span> *<span class="keyword">this</span>; }
00285 
<a name="l00292"></a><a class="code" href="classaeVector3.php#a11">00292</a>         <span class="keyword">inline</span> <a class="code" href="classaeVector3.php">aeVector3</a> <a class="code" href="classaeVector3.php#a11">operator-</a>()<span class="keyword"> const </span>{ <span class="keywordflow">return</span> <a class="code" href="classaeVector3.php#a0">aeVector3</a>(-x, -y, -z); }
00293 
<a name="l00301"></a><a class="code" href="classaeVector3.php#a12">00301</a>         <span class="keyword">inline</span> <span class="keywordtype">void</span> <a class="code" href="classaeVector3.php#a12">Set</a>(<span class="keywordtype">float</span> nx, <span class="keywordtype">float</span> ny, <span class="keywordtype">float</span> nz) {
00302                 x = nx;
00303                 y = ny;
00304                 z = nz;
00305         }
00306 
<a name="l00312"></a><a class="code" href="classaeVector3.php#a13">00312</a>         <span class="keyword">inline</span> <span class="keywordtype">void</span> <a class="code" href="classaeVector3.php#a12">Set</a>(<span class="keyword">const</span> <a class="code" href="classaeVector3.php">aeVector3</a> &amp;v) {
00313                 x = v.x;
00314                 y = v.y;
00315                 z = v.z;
00316         }
00317 
00324         <span class="keywordtype">void</span> <a class="code" href="classaeVector3.php#a14">Cross</a>(<span class="keyword">const</span> <a class="code" href="classaeVector3.php">aeVector3</a> &amp;v1, <span class="keyword">const</span> <a class="code" href="classaeVector3.php">aeVector3</a> &amp;v2);
00325 
00332         <span class="keywordtype">float</span> <a class="code" href="classaeVector3.php#a15">Magnitude</a>() <span class="keyword">const</span>;
00333 
<a name="l00341"></a><a class="code" href="classaeVector3.php#a16">00341</a>         <a class="code" href="classaeVector3.php">aeVector3</a> <a class="code" href="classaeVector3.php#a16">Unit</a>()<span class="keyword"> const </span>{ <span class="keywordflow">return</span> this-&gt;<a class="code" href="classaeVector3.php#a17">Normalize</a>(); }
00342 
00349         <a class="code" href="classaeVector3.php">aeVector3</a> <a class="code" href="classaeVector3.php#a17">Normalize</a>() <span class="keyword">const</span>;
00350 };
00351 
00352 <span class="preprocessor">#endif // __AELIB_AEGEOM_VECTOR3_H__</span>
</pre></div><hr><address style="align: right;"><small>Generated on Sun Mar 2 01:14:22 2003 for AE Engine by
<a href="http://www.doxygen.org/index.html">
<img src="doxygen.png" alt="doxygen" align="middle" border=0 
width=110 height=53></a>1.3-rc2 </small></address>
</body>
</html>