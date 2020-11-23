<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<html><head><meta http-equiv="Content-Type" content="text/html;charset=iso-8859-1">
<title>vector4.h Source File</title>
<link href="doxygen.css" rel="stylesheet" type="text/css">
</head><body>
<!-- Generated by Doxygen 1.3-rc2 -->
<center>
<a class="qindex" href="index.php">Main Page</a> &nbsp; <a class="qindex" href="modules.php">Modules</a> &nbsp; <a class="qindex" href="hierarchy.php">Class Hierarchy</a> &nbsp; <a class="qindex" href="classes.php">Alphabetical List</a> &nbsp; <a class="qindex" href="annotated.php">Compound List</a> &nbsp; <a class="qindex" href="files.php">File List</a> &nbsp; <a class="qindex" href="functions.php">Compound Members</a> &nbsp; </center>
<hr><h1>vector4.h</h1><div class="fragment"><pre>00001 <span class="comment">/*</span>
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
00022 <span class="preprocessor">#ifndef __AELIB_AEGEOM_VECTOR4_H__</span>
00023 <span class="preprocessor"></span><span class="preprocessor">#define __AELIB_AEGEOM_VECTOR4_H__</span>
00024 <span class="preprocessor"></span>
00025 <span class="preprocessor">#define ONLY_INCLUDE_STD</span>
00026 <span class="preprocessor"></span><span class="preprocessor">#include &lt;aedefs.h&gt;</span>
00027 <span class="preprocessor">#undef ONLY_INCLUDE_STD</span>
00028 <span class="preprocessor"></span>
<a name="l00033"></a><a class="code" href="classaeVector4.php">00033</a> <span class="keyword">class </span><a class="code" href="classaeVector4.php">aeVector4</a> {
00034         AECF_CNDEF
00035 
00036  <span class="keyword">public</span>:
00041         <a class="code" href="classaeVector4.php#a0">aeVector4</a>();
00042 
<a name="l00051"></a><a class="code" href="classaeVector4.php#a1">00051</a>         <a class="code" href="classaeVector4.php#a0">aeVector4</a>(<span class="keywordtype">float</span> nx, <span class="keywordtype">float</span> ny, <span class="keywordtype">float</span> nz, <span class="keywordtype">float</span> nw = 1) : <a class="code" href="classaeVector4.php#m0">x</a>(nx), <a class="code" href="classaeVector4.php#m1">y</a>(ny), <a class="code" href="classaeVector4.php#m2">z</a>(nz), <a class="code" href="classaeVector4.php#m3">w</a>(nw) {}
00052 
<a name="l00058"></a><a class="code" href="classaeVector4.php#a2">00058</a>         <a class="code" href="classaeVector4.php#a0">aeVector4</a>(<span class="keyword">const</span> <a class="code" href="classaeVector4.php">aeVector4</a> &amp;v) : <a class="code" href="classaeVector4.php#m0">x</a>(v.<a class="code" href="classaeVector4.php#m0">x</a>), <a class="code" href="classaeVector4.php#m1">y</a>(v.<a class="code" href="classaeVector4.php#m1">y</a>), <a class="code" href="classaeVector4.php#m2">z</a>(v.<a class="code" href="classaeVector4.php#m2">z</a>), <a class="code" href="classaeVector4.php#m3">w</a>(v.<a class="code" href="classaeVector4.php#m3">w</a>) {}
00059 
00060         ~<a class="code" href="classaeVector4.php">aeVector4</a>() {};
00061 
<a name="l00063"></a><a class="code" href="classaeVector4.php#m0">00063</a>         <span class="keywordtype">float</span> <a class="code" href="classaeVector4.php#m0">x</a>;
<a name="l00065"></a><a class="code" href="classaeVector4.php#m1">00065</a>         <span class="keywordtype">float</span> <a class="code" href="classaeVector4.php#m1">y</a>;
<a name="l00067"></a><a class="code" href="classaeVector4.php#m2">00067</a>         <span class="keywordtype">float</span> <a class="code" href="classaeVector4.php#m2">z</a>;
<a name="l00069"></a><a class="code" href="classaeVector4.php#m3">00069</a>         <span class="keywordtype">float</span> <a class="code" href="classaeVector4.php#m3">w</a>;
00070 
<a name="l00079"></a><a class="code" href="classaeVector4.php#l0">00079</a>         <span class="keyword">inline</span> <span class="keyword">friend</span> <a class="code" href="classaeVector4.php">aeVector4</a> <a class="code" href="classaeVector4.php#a10">operator+</a>(<span class="keyword">const</span> <a class="code" href="classaeVector4.php">aeVector4</a> &amp;v1, <span class="keyword">const</span> <a class="code" href="classaeVector4.php">aeVector4</a> &amp;v2) {
00080                 <span class="keywordflow">return</span> <a class="code" href="classaeVector4.php#a0">aeVector4</a>(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z, v1.w + v2.w);
00081         }
00082 
<a name="l00091"></a><a class="code" href="classaeVector4.php#l1">00091</a>         <span class="keyword">inline</span> <span class="keyword">friend</span> <a class="code" href="classaeVector4.php">aeVector4</a> <a class="code" href="classaeVector4.php#a11">operator-</a>(<span class="keyword">const</span> <a class="code" href="classaeVector4.php">aeVector4</a> &amp;v1, <span class="keyword">const</span> <a class="code" href="classaeVector4.php">aeVector4</a> &amp;v2) {
00092                 <span class="keywordflow">return</span> <a class="code" href="classaeVector4.php#a0">aeVector4</a>(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z, v1.w + v2.w);
00093         }
00094 
<a name="l00103"></a><a class="code" href="classaeVector4.php#l2">00103</a>         <span class="keyword">inline</span> <span class="keyword">friend</span> <span class="keywordtype">float</span> <a class="code" href="classaeVector4.php#l2">operator*</a>(<span class="keyword">const</span> <a class="code" href="classaeVector4.php">aeVector4</a> &amp;v1, <span class="keyword">const</span> <a class="code" href="classaeVector4.php">aeVector4</a> &amp;v2) {
00104                 <span class="keywordflow">return</span> (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z) + (v1.w * v2.w);
00105         }
00106 
<a name="l00115"></a><a class="code" href="classaeVector4.php#l3">00115</a>         <span class="keyword">inline</span> <span class="keyword">friend</span> <a class="code" href="classaeVector4.php">aeVector4</a> <a class="code" href="classaeVector4.php#l3">operator%</a>(<span class="keyword">const</span> <a class="code" href="classaeVector4.php">aeVector4</a> &amp;v1, <span class="keyword">const</span> <a class="code" href="classaeVector4.php">aeVector4</a> &amp;v2) {
00116                 <span class="keywordflow">return</span> <a class="code" href="classaeVector4.php#a0">aeVector4</a>((v1.x * v2.y - v1.y * v2.x) + (v1.x * v2.z - v1.z * v2.x) +
00117                                                  (v1.y * v2.z - v1.z * v2.y),
00118                                                  (v1.z * v2.y - v1.y * v2.z) + (v1.y * v2.w - v1.w * v2.y) +
00119                                                  (v1.z * v2.w - v1.w * v2.z),
00120                                                  (v1.x * v2.z - v1.z * v2.x) + (v1.w * v2.x - v1.x * v2.w) +
00121                                                  (v1.z * v2.w - v1.w * v2.z),
00122                                                  (v1.y * v1.x - v1.x * v2.y) + (v1.w * v2.x - v1.x * v2.w) +
00123                                                  (v1.w * v2.y - v1.y * v2.w));
00124         }
00125 
<a name="l00134"></a><a class="code" href="classaeVector4.php#l4">00134</a>         <span class="keyword">inline</span> <span class="keyword">friend</span> <a class="code" href="classaeVector4.php">aeVector4</a> <a class="code" href="classaeVector4.php#l2">operator*</a>(<span class="keyword">const</span> <a class="code" href="classaeVector4.php">aeVector4</a> &amp;v1, <span class="keywordtype">float</span> s) {
00135                 <span class="keywordflow">return</span> <a class="code" href="classaeVector4.php#a0">aeVector4</a>(v1.x * s, v1.y * s, v1.z * s, v1.w * s);
00136         }
00137 
<a name="l00146"></a><a class="code" href="classaeVector4.php#l5">00146</a>         <span class="keyword">inline</span> <span class="keyword">friend</span> <a class="code" href="classaeVector4.php">aeVector4</a> <a class="code" href="classaeVector4.php#l2">operator*</a>(<span class="keywordtype">float</span> s, <span class="keyword">const</span> <a class="code" href="classaeVector4.php">aeVector4</a> &amp;v1) {
00147                 <span class="keywordflow">return</span> <a class="code" href="classaeVector4.php#a0">aeVector4</a>(s * v1.x, s * v1.y, s * v1.z, s * v1.w);
00148         }
00149 
<a name="l00158"></a><a class="code" href="classaeVector4.php#l6">00158</a>         <span class="keyword">inline</span> <span class="keyword">friend</span> <a class="code" href="classaeVector4.php">aeVector4</a> <a class="code" href="classaeVector4.php#l2">operator*</a>(<span class="keyword">const</span> <a class="code" href="classaeVector4.php">aeVector4</a> &amp;v1, <span class="keywordtype">int</span> s) {
00159                 <span class="keywordflow">return</span> v1 * (float)s;
00160         }
00161 
<a name="l00170"></a><a class="code" href="classaeVector4.php#l7">00170</a>         <span class="keyword">inline</span> <span class="keyword">friend</span> <a class="code" href="classaeVector4.php">aeVector4</a> <a class="code" href="classaeVector4.php#l2">operator*</a>(<span class="keywordtype">int</span> s, <span class="keyword">const</span> <a class="code" href="classaeVector4.php">aeVector4</a> &amp;v1) {
00171                 <span class="keywordflow">return</span> (float)s * v1;
00172         }
00173 
<a name="l00182"></a><a class="code" href="classaeVector4.php#l8">00182</a>         <span class="keyword">inline</span> <span class="keyword">friend</span> <a class="code" href="classaeVector4.php">aeVector4</a> <a class="code" href="classaeVector4.php#l8">operator/</a>(<span class="keyword">const</span> <a class="code" href="classaeVector4.php">aeVector4</a> &amp;v1, <span class="keywordtype">float</span> s) {
00183                 s = 1.0f / s;
00184                 <span class="keywordflow">return</span> <a class="code" href="classaeVector4.php#a0">aeVector4</a>(v1.x * s, v1.y * s, v1.z * s, v1.w * s);
00185         }
00186 
<a name="l00195"></a><a class="code" href="classaeVector4.php#l9">00195</a>         <span class="keyword">inline</span> <span class="keyword">friend</span> <a class="code" href="classaeVector4.php">aeVector4</a> <a class="code" href="classaeVector4.php#l8">operator/</a>(<span class="keyword">const</span> <a class="code" href="classaeVector4.php">aeVector4</a> &amp;v1, <span class="keywordtype">int</span> s) {
00196                 <span class="keywordflow">return</span> (v1 / (float)s);
00197         }
00198 
<a name="l00207"></a><a class="code" href="classaeVector4.php#l10">00207</a>         <span class="keyword">inline</span> <span class="keyword">friend</span> <span class="keywordtype">bool</span> <a class="code" href="classaeVector4.php#l10">operator==</a>(<span class="keyword">const</span> <a class="code" href="classaeVector4.php">aeVector4</a> &amp;v1, <span class="keyword">const</span> <a class="code" href="classaeVector4.php">aeVector4</a> &amp;v2) {
00208                 <span class="keywordflow">return</span> v1.x == v2.x &amp;&amp; v1.y == v2.y &amp;&amp; v1.z == v2.z &amp;&amp; v1.w == v2.w;
00209         }
00210 
<a name="l00219"></a><a class="code" href="classaeVector4.php#l11">00219</a>         <span class="keyword">inline</span> <span class="keyword">friend</span> <span class="keywordtype">bool</span> <a class="code" href="classaeVector4.php#l11">operator!=</a>(<span class="keyword">const</span> <a class="code" href="classaeVector4.php">aeVector4</a> &amp;v1, <span class="keyword">const</span> <a class="code" href="classaeVector4.php">aeVector4</a> &amp;v2) {
00220                 <span class="keywordflow">return</span> v1.x != v2.x || v1.y != v2.y || v1.z != v2.z || v1.w != v2.w;
00221         }
00222 
<a name="l00230"></a><a class="code" href="classaeVector4.php#a4">00230</a>         <span class="keyword">inline</span> <span class="keywordtype">float</span> <a class="code" href="classaeVector4.php#a4">operator[]</a>(<span class="keywordtype">int</span> n)<span class="keyword"> const </span>{ <span class="keywordflow">return</span> !n ? x : n &amp; 1 ? y : n &amp; 2 ? z : w; }
00231 
<a name="l00239"></a><a class="code" href="classaeVector4.php#a5">00239</a>         <span class="keyword">inline</span> <span class="keywordtype">float</span> &amp; <a class="code" href="classaeVector4.php#a4">operator[]</a>(<span class="keywordtype">int</span> n) { <span class="keywordflow">return</span> !n ? x : n &amp; 1 ? y : n &amp; 2 ? z : w; }
00240 
<a name="l00248"></a><a class="code" href="classaeVector4.php#a6">00248</a>         <span class="keyword">inline</span> <a class="code" href="classaeVector4.php">aeVector4</a> &amp; <a class="code" href="classaeVector4.php#a6">operator+=</a>(<span class="keyword">const</span> <a class="code" href="classaeVector4.php">aeVector4</a> &amp;v1) {
00249                 x += v1.x;
00250                 y += v1.y;
00251                 z += v1.z;
00252                 w += v1.w;
00253                 <span class="keywordflow">return</span> *<span class="keyword">this</span>;
00254         }
00255 
<a name="l00263"></a><a class="code" href="classaeVector4.php#a7">00263</a>         <span class="keyword">inline</span> <a class="code" href="classaeVector4.php">aeVector4</a> &amp; <a class="code" href="classaeVector4.php#a7">operator-=</a>(<span class="keyword">const</span> <a class="code" href="classaeVector4.php">aeVector4</a> &amp;v1) {
00264                 x -= v1.x;
00265                 y -= v1.y;
00266                 z -= v1.z;
00267                 w -= v1.w;
00268                 <span class="keywordflow">return</span> *<span class="keyword">this</span>;
00269         }
00270 
<a name="l00278"></a><a class="code" href="classaeVector4.php#a8">00278</a>         <span class="keyword">inline</span> <a class="code" href="classaeVector4.php">aeVector4</a> &amp; <a class="code" href="classaeVector4.php#a8">operator*=</a>(<span class="keywordtype">float</span> s) {
00279                 x *= s;
00280                 y *= s;
00281                 z *= s;
00282                 w *= s;
00283                 <span class="keywordflow">return</span> *<span class="keyword">this</span>;
00284         }
00285 
<a name="l00293"></a><a class="code" href="classaeVector4.php#a9">00293</a>         <span class="keyword">inline</span> <a class="code" href="classaeVector4.php">aeVector4</a> &amp; <a class="code" href="classaeVector4.php#a9">operator/=</a>(<span class="keywordtype">float</span> s) {
00294                 s = 1.0f / s;
00295                 x *= s;
00296                 y *= s;
00297                 z *= s;
00298                 w *= s;
00299                 <span class="keywordflow">return</span> *<span class="keyword">this</span>;
00300         }
00301 
<a name="l00308"></a><a class="code" href="classaeVector4.php#a10">00308</a>         <span class="keyword">inline</span> <a class="code" href="classaeVector4.php">aeVector4</a> <a class="code" href="classaeVector4.php#a10">operator+</a>()<span class="keyword"> const </span>{ <span class="keywordflow">return</span> *<span class="keyword">this</span>; }
00309 
<a name="l00316"></a><a class="code" href="classaeVector4.php#a11">00316</a>         <span class="keyword">inline</span> <a class="code" href="classaeVector4.php">aeVector4</a> <a class="code" href="classaeVector4.php#a11">operator-</a>()<span class="keyword"> const </span>{ <span class="keywordflow">return</span> <a class="code" href="classaeVector4.php#a0">aeVector4</a>(-x, -y, -z, -w); }
00317 
<a name="l00326"></a><a class="code" href="classaeVector4.php#a12">00326</a>         <span class="keyword">inline</span> <span class="keywordtype">void</span> <a class="code" href="classaeVector4.php#a12">Set</a>(<span class="keywordtype">float</span> nx, <span class="keywordtype">float</span> ny, <span class="keywordtype">float</span> nz, <span class="keywordtype">float</span> nw) {
00327                 x = nx;
00328                 y = ny;
00329                 z = nz;
00330                 w = nw;
00331         }
00332 
<a name="l00338"></a><a class="code" href="classaeVector4.php#a13">00338</a>         <span class="keyword">inline</span> <span class="keywordtype">void</span> <a class="code" href="classaeVector4.php#a12">Set</a>(<span class="keyword">const</span> <a class="code" href="classaeVector4.php">aeVector4</a> &amp;v) {
00339                 x = v.x;
00340                 y = v.y;
00341                 z = v.z;
00342                 w = v.w;
00343         }
00344 
00351         <span class="keywordtype">void</span> <a class="code" href="classaeVector4.php#a14">Cross</a>(<span class="keyword">const</span> <a class="code" href="classaeVector4.php">aeVector4</a> &amp;v1, <span class="keyword">const</span> <a class="code" href="classaeVector4.php">aeVector4</a> &amp;v2);
00352 
00359         <span class="keywordtype">float</span> <a class="code" href="classaeVector4.php#a15">Magnitude</a>() <span class="keyword">const</span>;
00360 
<a name="l00368"></a><a class="code" href="classaeVector4.php#a16">00368</a>         <a class="code" href="classaeVector4.php">aeVector4</a> <a class="code" href="classaeVector4.php#a16">Unit</a>()<span class="keyword"> const </span>{ <span class="keywordflow">return</span> this-&gt;<a class="code" href="classaeVector4.php#a17">Normalize</a>(); }
00369 
00376         <a class="code" href="classaeVector4.php">aeVector4</a> <a class="code" href="classaeVector4.php#a17">Normalize</a>() <span class="keyword">const</span>;
00377 };
00378 
00379 <span class="preprocessor">#endif // __AELIB_AEGEOM_VECTOR4_H__</span>
</pre></div><hr><address style="align: right;"><small>Generated on Sun Mar 2 01:14:23 2003 for AE Engine by
<a href="http://www.doxygen.org/index.html">
<img src="doxygen.png" alt="doxygen" align="middle" border=0 
width=110 height=53></a>1.3-rc2 </small></address>
</body>
</html>