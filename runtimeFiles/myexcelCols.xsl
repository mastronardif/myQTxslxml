<xsl:stylesheet
version="2.0"
xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
<xsl:output method="xml" indent="yes"/>
<!--last Modified 6/12/14 11:12AM
Purpose:  Used to create ____ for report ___,
-->
<xsl:key name='string' match='strings/string' use='@id' />
<xsl:variable name="strings" select="document('list02.xml')/strings"/>

<xsl:template match="/">
<xsl:comment>FM xslt generated from file _( 4/28/14)</xsl:comment>

<html>

<body>
 
BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB
<xsl:variable name="celno">1399</xsl:variable>
celno[<xsl:value-of select="$celno"/>]
   <xsl:call-template name="getNameFromNumber">
     <xsl:with-param name="num"><xsl:value-of select="$celno"/></xsl:with-param>	 
    </xsl:call-template>
 	____________________________________
	____________________________________

	
	<xsl:call-template name="for.loop33">
     <xsl:with-param name="i">1</xsl:with-param>
     <xsl:with-param name="count">1600</xsl:with-param>
    </xsl:call-template>
	
<!--	
    <xsl:call-template name="for.loop22">
     <xsl:with-param name="i">0</xsl:with-param>
     <xsl:with-param name="count">330</xsl:with-param>
    </xsl:call-template>
-->	
 
<!--
    the excel col for col 330
    
	000000000000
    <xsl:call-template name="num2alpha">
     <xsl:with-param name="nn">28</xsl:with-param>
     <xsl:with-param name="rrr"></xsl:with-param>
    </xsl:call-template>
11111111111111	

-->

</body>
</html>

 </xsl:template>
 
   <!-- 
  http://stackoverflow.com/questions/3302857/algorithm-to-get-the-excel-like-column-name-of-a-number
  function getNameFromNumber($num) {
    $numeric = ($num - 1) % 26;
    $letter = chr(65 + $numeric);
    $num2 = intval(($num - 1) / 26);
    if ($num2 > 0) {
        return getNameFromNumber($num2) . $letter;
    } else {
        return $letter;
    }
}
  -->
  
 <xsl:template name="getNameFromNumber">
  <xsl:param name="num"      />
  <xsl:param name="excelCol"      />
  
  <xsl:variable name="numeric"><xsl:value-of select="(($num)-1) mod 26"/></xsl:variable>

  <!--
  num [<xsl:value-of select="$num"/>]
  numeric <xsl:value-of select="$numeric"/> 000numeric
  excelCol [<xsl:value-of select="$excelCol"/>]
  --> 
   <xsl:variable name="letter"> <xsl:value-of select="substring('ABCDEFGHIJKLMNOPQRSTUVWXYZ', $numeric+1, 1)"/></xsl:variable>

  <xsl:variable name="n0"><xsl:value-of select="(($num) - 1) div 26"/></xsl:variable>
<!--
	$n0 <xsl:value-of select="$n0"/> 000$n0
	zzz <xsl:value-of select="($n0) "/> 000zzz
	aaa <xsl:value-of select="( (floor($n0)*($n0 >=0)) + (ceiling($n0)*(not($n0 >=0))) )"/> 000aaa
-->

   <xsl:variable name="num2"><xsl:value-of select="( (floor($n0)*($n0 >=0)) + (ceiling($n0)*not($n0 >=0)) )"/></xsl:variable> 
<!-- $num2  <xsl:value-of select="$num2"/>  000num2 -->
 <!--floor(.)*(. >= 0)    +   ceiling(.) * not(. >= 0) -->
 <!-- <xsl:value-of select="( (floor($n0)*($n0 >=0)) + (ceiling($n0)*not($n0 >=0)) )"/>
-->
 <!-- $letter [<xsl:value-of select="$letter"/>] -->
  
  <xsl:choose>
  <xsl:when test="$num2 &gt; 0">
  
   <xsl:call-template name="getNameFromNumber">
     <xsl:with-param name="num"><xsl:value-of select="$num2" /></xsl:with-param>
	 <xsl:with-param name="excelCol"><xsl:value-of select="$excelCol" /><xsl:value-of select="$letter" /></xsl:with-param>	 
    </xsl:call-template>
  	<!-- {{{{{ <xsl:value-of select="$letter" /> }}}}} -->
<xsl:value-of select="$letter" />
   </xsl:when>
  <xsl:otherwise>
    <!-- DDDD[<xsl:value-of select="$letter" />]EEE -->
<xsl:value-of select="$letter" />
  </xsl:otherwise>
</xsl:choose>

   </xsl:template>
   
 <xsl:template name="for.loop33">
   <xsl:param name="i"      />
   <xsl:param name="count"  />

   <xsl:variable name="celno"><xsl:value-of select="$i"/></xsl:variable>
   <!-- 11111111111111111111111111111111111111 -->
<!-- celno[<xsl:value-of select="$celno"/>] -->
   <xsl:call-template name="getNameFromNumber">
     <xsl:with-param name="num"><xsl:value-of select="$celno"/></xsl:with-param>	 
    </xsl:call-template>
	<xsl:text> 
	</xsl:text>
	<!--
 	____________________________________
	 222222222222222222222222222222222222 
	 -->
      <!--begin_: RepeatTheLoopUntilFinished-->
   <xsl:if test="$i &lt;= $count">
      <xsl:call-template name="for.loop33">
          <xsl:with-param name="i">
              <xsl:value-of select="$i + 1"/>
          </xsl:with-param>
          <xsl:with-param name="count">
              <xsl:value-of select="$count"/>
          </xsl:with-param>
      </xsl:call-template>
   </xsl:if>

  </xsl:template>
   
   
   
   
   
 
 <xsl:template name="for.loop22">

   <xsl:param name="i"      />
   <xsl:param name="count"  />

   <!--begin_: Line_by_Line_Output -->
   <xsl:if test="$i &lt;= $count">
    
<xsl:value-of select="substring('ABCDEFGHIJKLMNOPQRSTUVWXYZ',$i,1)"/>    
 <b><xsl:value-of select="$i" /></b>
 
     <xsl:call-template name="num2alpha">
     <xsl:with-param name="nn"><xsl:value-of select="$i" /></xsl:with-param>	 
     <xsl:with-param name="rrr"></xsl:with-param>
    </xsl:call-template>
   </xsl:if>

   <!--begin_: RepeatTheLoopUntilFinished-->
   <xsl:if test="$i &lt;= $count">
      <xsl:call-template name="for.loop22">
          <xsl:with-param name="i">
              <xsl:value-of select="$i + 1"/>
          </xsl:with-param>
          <xsl:with-param name="count">
              <xsl:value-of select="$count"/>
          </xsl:with-param>
      </xsl:call-template>
   </xsl:if>

  </xsl:template>

	
   <xsl:template name="num2alpha">
	<xsl:param name="nn"/>
	<xsl:param name="rrr"/>
   
<!--
   input00 num2alpha (<xsl:value-of select="$nn"/>), (<xsl:value-of select="$rrr"/>) input11
-->
   <xsl:if test="$nn &lt;0">
  </xsl:if>
THECELL <xsl:value-of select="$rrr"/> CELL

 
   <!--begin_: RepeatTheLoopUntilFinished-->
   <xsl:if test="$nn &gt;= 0">
      <xsl:call-template name="num2alpha">
          <xsl:with-param name="nn">
		  <!--floor(.)*(. >= 0)    +   ceiling(.) * not(. >= 0) -->
          <xsl:value-of select="( ((floor($nn div 26))*($nn >=0) + ceiling($nn div 26)*not($nn >=0)) -1)"/>
		  <!-- <xsl:value-of select="(($nn div 26) -1)"/> -->
          </xsl:with-param>
<xsl:with-param name="rrr"><xsl:value-of select="substring('ABCDEFGHIJKLMNOPQRSTUVWXYZ', (($nn+1) mod 26),1)"/><xsl:value-of select="$rrr"/></xsl:with-param>
      </xsl:call-template>

   </xsl:if>

  </xsl:template>
 
 <!--begin_: Define_The_Output_Loop -->
  <xsl:template name="for.loop">

   <xsl:param name="i"      />
   <xsl:param name="count"  />

   <!--begin_: Line_by_Line_Output -->
   <xsl:if test="$i &lt;= $count">
    
<xsl:value-of select="substring('ABCDEFGHIJKLMNOPQRSTUVWXYZ',$i,1)"/>    
 <b><xsl:value-of select="$i" />.</b>Hello world!
   </xsl:if>

   <!--begin_: RepeatTheLoopUntilFinished-->
   <xsl:if test="$i &lt;= $count">
      <xsl:call-template name="for.loop">
          <xsl:with-param name="i">
              <xsl:value-of select="$i + 1"/>
          </xsl:with-param>
          <xsl:with-param name="count">
              <xsl:value-of select="$count"/>
          </xsl:with-param>
      </xsl:call-template>
   </xsl:if>

  </xsl:template>
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
     <xsl:template name="XMLTOTITLE221">
	    <!-- My globals BEGIN FM when you get a chance see if you can make this global. -->	
        <xsl:variable name="numOfQuestions" select="count(/ROOT/SESSION/QUESTIONS/*)"/> 
 		<xsl:variable name="numOfStudents" select="count(/ROOT/SESSION/STUDENTS/*)"/> 
        <xsl:variable name="myFirstStudentRow" select="8"/> 
        <xsl:variable name="myLastStudentRow" select="8+($numOfStudents)-1"/> 
        <xsl:variable name="myLastQuestionCol" select="6+($numOfQuestions)"/> 
		<xsl:variable name="myspans" select="concat('1:', $myLastQuestionCol)"/> 
		
		<xsl:variable name="row" select="6"/> 
    <!-- my globals end -->



    
		<row r="6" spans="{$myspans}" s="5" customFormat="1" ht="16">
			<c r="D6" s="86" t="inlineStr"><is> <t>Session Scores</t></is></c>
			
			<c r="E6" s="87"/>
			<c r="F6" s="88"/>
			
			<!-- <c r="G6" s="86" t="inlineStr"><is> <t>Session Scores</t></is></c> -->
			
			<xsl:for-each select="ROOT/SESSION/QUESTIONS/question">
			<c>
				<xsl:attribute name="r"><xsl:call-template name="EXCEL_COLUMNS33"><xsl:with-param name="bars" select="6+position()"/></xsl:call-template><xsl:value-of select="$row"/></xsl:attribute>
			
			 <xsl:choose>
                 <xsl:when test="position()  = 1">
                       <xsl:attribute name="s">86</xsl:attribute>
					   <xsl:attribute name="t">inlineStr</xsl:attribute>
					   <is> <t>Question Results</t></is>
                 </xsl:when>
                 <xsl:when test="position()  = last()">
                       <xsl:attribute name="s">88</xsl:attribute>
                 </xsl:when>
                 <xsl:otherwise>
                       <xsl:attribute name="s">87</xsl:attribute>
                 </xsl:otherwise>
           </xsl:choose>
			</c>
			</xsl:for-each>
			
			<!--<c r="G6" s="86" t="s">
				<v>29</v>
			</c><c r="H6" s="87"/>
			<c r="I6" s="87"/>
			<c r="J6" s="87"/>
			<c r="K6" s="88"/> -->
		</row>

  </xsl:template>

 
 <xsl:template name="QUESTIONS">
	<!-- <xsl:variable name="row" select="7"/> -->
	<xsl:variable name="row" select="7"/>
	<xsl:variable name="myFirstQuestionCol" select="7"/>
	
    <xsl:for-each select="ROOT/SESSION/QUESTIONS/question">
      <c t="inlineStr">
         <xsl:attribute name="r"><xsl:call-template name="EXCEL_COLUMNS33"><xsl:with-param name="bars" select="($myFirstQuestionCol)-1+position()"/></xsl:call-template><xsl:value-of select="$row"/></xsl:attribute>

           <xsl:choose>
                 <xsl:when test="position()  = 1">
                       <xsl:attribute name="s">46</xsl:attribute>
                 </xsl:when>
                 <xsl:when test="position()  = last()">
                       <xsl:attribute name="s">48</xsl:attribute>
                 </xsl:when>
                 <xsl:otherwise>
                       <xsl:attribute name="s">47</xsl:attribute>
                 </xsl:otherwise>
           </xsl:choose>

		<is><t>
			<xsl:choose>
			<xsl:when test="string-length(@name)>11">
                 <xsl:value-of select="substring (@name, 1, 10)"/>...
			</xsl:when>
			<xsl:otherwise>
                 <xsl:value-of select="@name" />
			</xsl:otherwise>
			</xsl:choose>
		</t></is>
     </c>

    </xsl:for-each>

 </xsl:template>

 
  <xsl:template name="STUDENTS">
  
	<xsl:for-each select="ROOT/SESSION/STUDENTS/student">

  <!-- my globals begin -->
      <!-- My globals BEGIN FM when you get a chance see if you can make this global. -->	
        <xsl:variable name="numOfQuestions" select="count(/ROOT/SESSION/QUESTIONS/*)"/> 
 		<xsl:variable name="numOfStudents" select="count(/ROOT/SESSION/STUDENTS/*)"/> 
        <xsl:variable name="myFirstStudentRow" select="8"/> 
        <xsl:variable name="myLastStudentRow" select="8+($numOfStudents)-1"/> 
		<xsl:variable name="myFirstQuestionCol" select="7"/>
        <xsl:variable name="myLastQuestionCol" select="6+($numOfQuestions)"/> 
		<xsl:variable name="myspans" select="concat('1:', $myLastQuestionCol)"/> 
		
		<xsl:variable name="row" select="8"/> 

		<xsl:variable name="pStudentRow" select="($myFirstStudentRow)-1+position()" />
    <!-- my globals end -->
		<row r="{7+position()}"  ht="16">
		<xsl:attribute name="spans"><xsl:value-of select="$myspans" /></xsl:attribute>
			<c r="A{7+position()}" s="37" t="inlineStr">
				<is> <t> <xsl:value-of select="@name"/> </t> </is> </c>
			<c r="B{7+position()}" s="37" t="inlineStr">
				<is> <t><xsl:value-of select="@StudentId"/></t> </is> </c>
				
			<c r="C{7+position()}" s="37" t="inlineStr">
				<is> <t><xsl:value-of select="@RemoteId"/></t> </is> </c>

<xsl:variable name="posn" select="$myFirstQuestionCol+position()" />



			<!-- Response Counts cols[DEF]-->
			<!--
			<c r="D{7+position()}" s="7" t="str">
			   <f>COUNTIF(J<xsl:value-of select="7+position()"/>:<xsl:call-template name="EXCEL_COLUMNS33"><xsl:with-param name="bars" select="$myLastQuestionCol"/></xsl:call-template>
			   <xsl:value-of select="$pStudentRow"/>,"&gt;0")</f> <v>1234</v>
			</c>
			<c r="E{7+position()}" s="2" t="str">
				<f>COUNTIF(J<xsl:value-of select="7+position()"/>:<xsl:call-template name="EXCEL_COLUMNS33"><xsl:with-param name="bars" select="$myLastQuestionCol"/></xsl:call-template>
				<xsl:value-of select="$pStudentRow"/>,"0")</f> <v>1234</v>
			</c>

			<c r="F{7+position()}" s="8" t="n">
				<f>COUNTIF(J<xsl:value-of select="7+position()"/>:<xsl:call-template name="EXCEL_COLUMNS33"><xsl:with-param name="bars" select="$myLastQuestionCol"/></xsl:call-template>
				<xsl:value-of select="$pStudentRow"/>,"(NR)")</f> <v>1234</v>
			</c>
			-->

			<!-- Session Scores cols[GHI] DEF -->
			<c r="D{7+position()}" s="76" t="str">
			   <f>SUM(E<xsl:value-of select="$pStudentRow"/>:F<xsl:value-of select="$pStudentRow"/>)</f> <v>1234</v></c>
			<c r="E{7+position()}" s="4" t="str">
				<f>SUM(G<xsl:value-of select="$pStudentRow" />:<xsl:call-template name="EXCEL_COLUMNS33"><xsl:with-param name="bars" select="$myLastQuestionCol"/></xsl:call-template>
					    <xsl:value-of select="$pStudentRow" />)</f>	<v>4</v>
			</c>
			<c r="F{7+position()}" s="4" t="n"><v><xsl:value-of select="@Partic"/></v></c>
			
			<!-- read q results for student ____ (pivot) begin -->				
			<xsl:for-each select="qr/q">

	<xsl:variable name="vStyleScore">	
    <xsl:choose>
      <xsl:when test="@score = '0'">
		<xsl:value-of select='53' />
      </xsl:when>
	  
	  <xsl:when test="@score = '(NR)'">
        <xsl:value-of select='49' />
      </xsl:when>
	  
      <xsl:otherwise>
		<xsl:value-of select='4' />
      </xsl:otherwise>
    </xsl:choose>
	</xsl:variable>
	
	<c t="n">

        <xsl:attribute name="r"><xsl:call-template name="EXCEL_COLUMNS33"><xsl:with-param name="bars" select="($myFirstQuestionCol)-1+position()"/></xsl:call-template><xsl:value-of select="$pStudentRow"/></xsl:attribute>

	<xsl:choose>
      <xsl:when test="@score = '0'">
		<xsl:attribute name="s">53</xsl:attribute>
		 <v> <xsl:value-of select="@score"/> </v> 
      </xsl:when>
	  
	  <xsl:when test="@score = '(NR)'">
		<xsl:attribute name="s">49</xsl:attribute>
		 <xsl:attribute name="t">inlineStr</xsl:attribute>
		 <is> <t> <xsl:value-of select="@score"/> </t> </is>
      </xsl:when>
	  
      <xsl:otherwise>
	   <xsl:attribute name="s">4</xsl:attribute>
		<v> <xsl:value-of select="@score"/> </v> 
      </xsl:otherwise>
    </xsl:choose>	 
	</c>
				
			</xsl:for-each>
			<!-- read q results for student ____ (pivot) end -->				
		</row>			
 </xsl:for-each>
 </xsl:template>
 
   <xsl:template name="POSSIBLE_POINTS">
 <!-- My globals BEGIN FM when you get a chance see if you can make this global. -->	
    <xsl:variable name="numOfQuestions" select="count(/ROOT/SESSION/QUESTIONS/*)"/> 
 	<xsl:variable name="numOfStudents" select="count(/ROOT/SESSION/STUDENTS/*)"/> 
   <!--  <xsl:variable name="myFirstStudentRow" select="8"/> -->

    <xsl:variable name="myLastStudentRow" select="8+($numOfStudents)-1"/> 
    <xsl:variable name="myFirstQuestionCol" select="7"/> 
	<xsl:variable name="myLastQuestionCol" select="6+($numOfQuestions)"/> 
	<xsl:variable name="myspans" select="concat('1:', $myLastQuestionCol)"/> 
		
	<xsl:variable name="row" select="8+$numOfStudents"/> 
<!-- END -->   
				
	<row r="{$row}" s="3" customFormat="1" ht="13">
	<xsl:attribute name="spans"><xsl:value-of select="$myspans" /></xsl:attribute>
		
	<xsl:for-each select="ROOT/SESSION">		
			<c r="A{$row}" s="85"/>
			<c r="B{$row}" s="85"/>
			<!--<c r="C{$row}" s="85"/>
			<c r="D{$row}" s="13"/>
			<c r="E{$row}" s="13"/> -->
			<c r="C{$row}" s="42" t="inlineStr"><is> <t>Possible Points</t></is></c>
	  
			<c r="D{$row}" s="57">
				<f>SUM(E<xsl:value-of select="$row"/>:F<xsl:value-of select="$row"/>)</f><v>7</v>
			</c>
			<c r="E{$row}" s="12"> <v><xsl:value-of select="@perf"/> </v></c>
			<c r="F{$row}" s="12"> <v><xsl:value-of select="@part"/> </v></c>
				
			<xsl:for-each select="./QUESTIONS/question">
			<xsl:variable name="pQuestionCol" select="($myFirstQuestionCol)-1+position()" />
                                <c t="n">
					<xsl:attribute name="r"><xsl:call-template name="EXCEL_COLUMNS33"><xsl:with-param name="bars" select="$pQuestionCol"/></xsl:call-template><xsl:value-of select="$row"/></xsl:attribute>
		
					<xsl:choose>
						<xsl:when test="position()  = 1">
							<xsl:attribute name="s">39</xsl:attribute>
						</xsl:when>
						<xsl:when test="position()  = last()">
							<xsl:attribute name="s">31</xsl:attribute>
						</xsl:when>
						<xsl:otherwise>
							<xsl:attribute name="s">13</xsl:attribute>
						</xsl:otherwise>
					</xsl:choose>
				<v><xsl:value-of select="@possiblePoints"/> </v>
				</c>
			</xsl:for-each>
 </xsl:for-each>
 </row>
 </xsl:template>	

<xsl:template name="EXCEL_COLUMNS33">
    <xsl:param name="bars"/>
	<xsl:variable name="strings" select="document('list02.xml')/strings"/>
    <xsl:for-each select='$strings'>
		 <xsl:value-of select='key("string", $bars)'/>
    </xsl:for-each>
</xsl:template>
 
 <xsl:template name="AVERAGE_POINTS">
 <!-- My globals BEGIN FM when you get a chance see if you can make this global. -->	
    <xsl:variable name="numOfQuestions" select="count(/ROOT/SESSION/QUESTIONS/*)"/> 
 	<xsl:variable name="numOfStudents" select="count(/ROOT/SESSION/STUDENTS/*)"/> 
    <xsl:variable name="myFirstStudentRow" select="8"/> 
    <xsl:variable name="myLastStudentRow" select="8+($numOfStudents)-1"/> 
	<xsl:variable name="myFirstQuestionCol" select="7"/> 
    <xsl:variable name="myLastQuestionCol" select="6+($numOfQuestions)"/> 
	<xsl:variable name="myspans" select="concat('1:', $myLastQuestionCol)"/> 
		
	<xsl:variable name="row" select="1+8+$numOfStudents"/> 
<!-- END -->
                
        <row r="{$row}" s="3" customFormat="1" ht="13">
	<xsl:attribute name="spans"><xsl:value-of select="$myspans" /></xsl:attribute>
        
		<xsl:for-each select="ROOT/SESSION">		
			<c r="A{$row}" s="14"/>
			<c r="B{$row}" s="14"/>
			<!--<c r="C{$row}" s="14"/>
			<c r="D{$row}" s="14"/>
			<c r="E{$row}" s="14"/> -->
			<c r="C{$row}" s="28" t="inlineStr"> <is> <t>Average Points</t></is></c>
			
                        <c r="D{$row}" s="57">
                                <!--<f>AVERAGE(G8:G<xsl:value-of select="7+$numOfStudents"/>)</f><v>7</v>-->
								<f>SUM(E<xsl:value-of select="$row"/>:F<xsl:value-of select="$row"/>)</f><v>7</v>
			</c>      
                        <c r="E{$row}" s="12">
                                <f>AVERAGE(E8:E<xsl:value-of select="7+$numOfStudents" />)</f><v>6</v>
			</c>
                        <c r="F{$row}" s="12">
                                <f>AVERAGE(F8:F<xsl:value-of select="7+$numOfStudents" />)</f><v>6</v>
			</c>			
			<xsl:for-each select="./QUESTIONS/question">
				<xsl:variable name="pQuestionCol" select="($myFirstQuestionCol)-1+position()" />
                                <c t="n">
                <xsl:attribute name="r"><xsl:call-template name="EXCEL_COLUMNS33"><xsl:with-param name="bars" select="$pQuestionCol"/></xsl:call-template><xsl:value-of select="$row"/></xsl:attribute>
					<xsl:choose>
						<xsl:when test="position()  = 1">
                                                        <xsl:attribute name="s">39</xsl:attribute>
						</xsl:when>
						<xsl:when test="position()  = last()">
                                                        <xsl:attribute name="s">31</xsl:attribute>
						</xsl:when>
						<xsl:otherwise>
                                                        <xsl:attribute name="s">13</xsl:attribute>
						</xsl:otherwise>
					</xsl:choose>
						<f>AVERAGE(<xsl:call-template name="EXCEL_COLUMNS33"><xsl:with-param name="bars" select="$pQuestionCol"/></xsl:call-template>		
						<xsl:value-of select="$myFirstStudentRow"/>:<xsl:call-template name="EXCEL_COLUMNS33"><xsl:with-param name="bars" select="$pQuestionCol"/></xsl:call-template>       
						<xsl:value-of select="$myLastStudentRow"/>)</f>
				<v><xsl:value-of select="@possiblePoints"/> </v>
				</c>
			</xsl:for-each>
 </xsl:for-each>
 </row>
 </xsl:template>
 
 <xsl:template name="AVERAGE_PERCENT">
 		
<!-- My globals BEGIN FM when you get a chance see if you can make this global. -->	
        <xsl:variable name="numOfQuestions" select="count(/ROOT/SESSION/QUESTIONS/*)"/> 
 		<xsl:variable name="numOfStudents" select="count(/ROOT/SESSION/STUDENTS/*)"/> 
        <xsl:variable name="myFirstStudentRow" select="8"/> 
        <xsl:variable name="myLastStudentRow" select="8+($numOfStudents)-1"/>
		<xsl:variable name="myFirstQuestionCol" select="7"/> 		
        <xsl:variable name="myLastQuestionCol" select="6+($numOfQuestions)"/> 
		<xsl:variable name="myspans" select="concat('1:', $myLastQuestionCol)"/> 
		
		<xsl:variable name="row" select="2+8+$numOfStudents"/> 
<!-- END -->
 
	<row r="{$row}" s="9" customFormat="1" ht="13">
		<xsl:attribute name="spans"><xsl:value-of select="$myspans" /></xsl:attribute>
		<xsl:for-each select="ROOT/SESSION">				
		<c r="B{$row}" s="14"/>
		<!--<c r="C{$row}" s="40"/>
		<c r="D{$row}" s="40"/>
		<c r="E{$row}" s="28"/>	-->	
		<c r="C{$row}" s="28" t="inlineStr"> <is> <t>Average %</t></is></c>
		
		<c r="D{$row}" s="59">
			<f>SUM(E<xsl:value-of select="$row"/>:F<xsl:value-of select="$row"/>)</f><v>7</v>
		</c>
		<c r="E{$row}" s="30">
			<f>(E<xsl:value-of select="-1+$row" />/E<xsl:value-of select="-2+$row" />)</f><v>0.123</v>
		</c>
		<c r="F{$row}" s="30">
			<f>(F<xsl:value-of select="-1+$row" />/F<xsl:value-of select="-2+$row" />)</f><v>0.234</v>
		</c>
				
			<xsl:for-each select="./QUESTIONS/question">
				<xsl:variable name="pQuestionCol" select="($myFirstQuestionCol)-1+position()" />
				<c s="39" t="n">
 				<xsl:attribute name="r"><xsl:call-template name="EXCEL_COLUMNS33"><xsl:with-param name="bars" select="$pQuestionCol"/></xsl:call-template><xsl:value-of select="$row"/></xsl:attribute>								
					<xsl:choose>
						<xsl:when test="position()  = 1">
							<xsl:attribute name="s">30</xsl:attribute>
						</xsl:when>
						<xsl:when test="position()  = last()">
							<xsl:attribute name="s">30</xsl:attribute>
						</xsl:when>
						<xsl:otherwise>
							<xsl:attribute name="s">30</xsl:attribute>
						</xsl:otherwise>
					</xsl:choose>
					<f>IF(<xsl:call-template name="EXCEL_COLUMNS33"><xsl:with-param name="bars" select="$pQuestionCol"/></xsl:call-template><xsl:value-of select="-2+$row" />=0, 0, <xsl:call-template name="EXCEL_COLUMNS33"><xsl:with-param name="bars" select="$pQuestionCol"/></xsl:call-template><xsl:value-of select="-1+$row" />/<xsl:call-template name="EXCEL_COLUMNS33"><xsl:with-param name="bars" select="$pQuestionCol"/></xsl:call-template><xsl:value-of select="-2+$row" />) </f>
				<v><xsl:value-of select="@possiblePoints"/> </v>
				</c>
			</xsl:for-each>
		
		</xsl:for-each>
		
	</row>
  </xsl:template>
  
  
    <xsl:template name="QUESTON_LABELS_FOOT">
  
  <!-- My globals BEGIN FM when you get a chance see if you can make this global. -->	
        <xsl:variable name="numOfQuestions" select="count(/ROOT/SESSION/QUESTIONS/*)"/> 
 		<xsl:variable name="numOfStudents" select="count(/ROOT/SESSION/STUDENTS/*)"/> 
        <xsl:variable name="myFirstStudentRow" select="8"/> 
        <xsl:variable name="myLastStudentRow" select="8+($numOfStudents)-1"/> 
		<xsl:variable name="myFirstQuestionCol" select="7"/> 	
        <xsl:variable name="myLastQuestionCol" select="6+($numOfQuestions)"/> 
		<xsl:variable name="myspans" select="concat('1:', $myLastQuestionCol)"/> 
		
		<xsl:variable name="row" select="3+8+$numOfStudents"/> 
<!-- END -->

	<row r="{$row}" s="27" customFormat="1" ht="16">
		<xsl:attribute name="spans"><xsl:value-of select="$myspans" /></xsl:attribute>
		<c r="A{$row}" s="25"/>
		<c r="B{$row}" s="25"/>
		<c r="C{$row}" s="25"/>
		<c r="D{$row}" s="26"/>
		<c r="E{$row}" s="26"/>
		<c r="F{$row}" s="26"/>				

	<xsl:for-each select="ROOT/SESSION/QUESTIONS/question">	
		<xsl:variable name="pQuestionCol" select="($myFirstQuestionCol)-1+position()" />
	 <c t="inlineStr">
		<xsl:attribute name="r"><xsl:call-template name="EXCEL_COLUMNS33"><xsl:with-param name="bars" select="$pQuestionCol"/></xsl:call-template><xsl:value-of select="$row"/></xsl:attribute>								

		<xsl:choose>
			<xsl:when test="position()  = 1">
				<xsl:attribute name="s">13</xsl:attribute>
			</xsl:when>
			<xsl:when test="position()  = last()">
				<xsl:attribute name="s">13</xsl:attribute>
			</xsl:when>
			<xsl:otherwise>
				<xsl:attribute name="s">13</xsl:attribute>
			</xsl:otherwise>
		</xsl:choose>
	</c>
	
	</xsl:for-each> 
	</row>
  </xsl:template>
  <xsl:template name="QUESTON_LABELS">
  
  <!-- My globals BEGIN FM when you get a chance see if you can make this global. -->	
        <xsl:variable name="numOfQuestions" select="count(/ROOT/SESSION/QUESTIONS/*)"/> 
 		<xsl:variable name="numOfStudents" select="count(/ROOT/SESSION/STUDENTS/*)"/> 
        <xsl:variable name="myFirstStudentRow" select="8"/> 
        <xsl:variable name="myLastStudentRow" select="8+($numOfStudents)-1"/> 
		<xsl:variable name="myFirstQuestionCol" select="10"/> 	
        <xsl:variable name="myLastQuestionCol" select="6+($numOfQuestions)"/> 
		<xsl:variable name="myspans" select="concat('1:', $myLastQuestionCol)"/> 
		
		<xsl:variable name="row" select="3+8+$numOfStudents"/> 
<!-- END -->

	<row r="{$row}" s="27" customFormat="1" ht="16">
		<xsl:attribute name="spans"><xsl:value-of select="$myspans" /></xsl:attribute>
		<c r="A{$row}" s="25"/>
		<c r="B{$row}" s="25"/>
		<c r="C{$row}" s="25"/>
		<c r="D{$row}" s="26"/>
		<c r="E{$row}" s="26"/>
		<c r="F{$row}" s="26"/>				

	<xsl:for-each select="ROOT/SESSION/QUESTIONS/question">	
		<xsl:variable name="pQuestionCol" select="($myFirstQuestionCol)-1+position()" />
	 <c t="inlineStr">
		<xsl:attribute name="r"><xsl:call-template name="EXCEL_COLUMNS33"><xsl:with-param name="bars" select="$pQuestionCol"/></xsl:call-template><xsl:value-of select="$row"/></xsl:attribute>								

		<xsl:choose>
			<xsl:when test="position()  = 1">
				<xsl:attribute name="s">46</xsl:attribute>
			</xsl:when>
			<xsl:when test="position()  = last()">
				<xsl:attribute name="s">48</xsl:attribute>
			</xsl:when>
			<xsl:otherwise>
				<xsl:attribute name="s">47</xsl:attribute>
			</xsl:otherwise>
		</xsl:choose>

	<is><t>
	<xsl:choose>
		<xsl:when test="string-length(@name)>11">
			<xsl:value-of select="substring (@name, 1, 10)"/>...
		</xsl:when>
		<xsl:otherwise>
			<xsl:value-of select="@name" />
		</xsl:otherwise>
	</xsl:choose>
	</t></is>
	</c>
	
	</xsl:for-each> 
	</row>
  </xsl:template>
  
  <xsl:template name="QUESTION_xyz_RESPONSES">
	<xsl:param name="row22"/>
	<xsl:param name="ResponseType"/>
   	<xsl:param name="first"/>
	<xsl:param name="middle"/>
	<xsl:param name="last"/>
    
	<!-- My globals BEGIN FM when you get a chance see if you can make this global. -->	
    <xsl:variable name="numOfQuestions" select="count(/ROOT/SESSION/QUESTIONS/*)"/> 
 	<xsl:variable name="numOfStudents" select="count(/ROOT/SESSION/STUDENTS/*)"/> 
    <xsl:variable name="myFirstStudentRow" select="8"/> 
    <xsl:variable name="myLastStudentRow" select="8+($numOfStudents)-1"/>
	<xsl:variable name="myFirstQuestionCol" select="10"/> 			
    <xsl:variable name="myLastQuestionCol" select="6+($numOfQuestions)"/> 
	<xsl:variable name="myspans" select="concat('1:', $myLastQuestionCol)"/> 
	
	<xsl:variable name="row" select="$row22"/>  <!-- //select="4+8+$numOfStudents"/> -->
<!-- END -->

	<row r="{$row}" s="27" customFormat="1" ht="16">
		<xsl:attribute name="spans"><xsl:value-of select="$myspans" /></xsl:attribute>
		<c r="A{$row}" s="11"/>
		<c r="B{$row}" s="11"/>
		<c r="C{$row}" s="11"/>
		<c r="D{$row}" s="63"/>		
		<c r="E{$row}" s="63"/>
		<c r="F{$row}" s="63"/>
		<c r="H{$row}" s="63"/>		
		<c r="I{$row}" s="14" t="inlineStr"> <is> <t><xsl:value-of select="$ResponseType" /></t></is></c>
		
		
		<xsl:for-each select="ROOT/SESSION/QUESTIONS/question">
			<xsl:variable name="pQuestionCol" select="($myFirstQuestionCol)-1+position()" />
			<c s="39" t="n">
                <xsl:attribute name="r"><xsl:call-template name="EXCEL_COLUMNS33"><xsl:with-param name="bars" select="$pQuestionCol"/></xsl:call-template><xsl:value-of select="$row"/></xsl:attribute>
				<xsl:attribute name="s">
                    <xsl:choose>
                        <xsl:when test="position()  = 1"><xsl:value-of select="$first" /></xsl:when>
                        <xsl:when test="position()  = last()"><xsl:value-of select="$last" /></xsl:when>					
                        <xsl:otherwise><xsl:value-of select="$middle" /></xsl:otherwise>
				</xsl:choose>		
                
                </xsl:attribute>						
					<xsl:choose>
					<xsl:when test="$ResponseType = 'Correct Responses'">
						<f>COUNTIF(<xsl:call-template name="EXCEL_COLUMNS33"><xsl:with-param name="bars" select="$pQuestionCol"/></xsl:call-template>		
						<xsl:value-of select="$myFirstStudentRow"/>:<xsl:call-template name="EXCEL_COLUMNS33"><xsl:with-param name="bars" select="$pQuestionCol"/></xsl:call-template>       
						<xsl:value-of select="$myLastStudentRow"/>, "&gt;0")</f>					
						<v><xsl:value-of select="@correctResponses"/> </v>						
					</xsl:when>
					
					<xsl:when test="$ResponseType = 'Incorrect Responses'">
						<f>COUNTIF(<xsl:call-template name="EXCEL_COLUMNS33"><xsl:with-param name="bars" select="$pQuestionCol"/></xsl:call-template>		
						<xsl:value-of select="$myFirstStudentRow"/>:<xsl:call-template name="EXCEL_COLUMNS33"><xsl:with-param name="bars" select="$pQuestionCol"/></xsl:call-template>       
						<xsl:value-of select="$myLastStudentRow"/>, "0")</f>					
						<v><xsl:value-of select="@correctResponses"/> </v>						
					</xsl:when>
					
					<xsl:when test="$ResponseType = 'No Responses'">
						<f>COUNTIF(<xsl:call-template name="EXCEL_COLUMNS33"><xsl:with-param name="bars" select="$pQuestionCol"/></xsl:call-template>		
						<xsl:value-of select="$myFirstStudentRow"/>:<xsl:call-template name="EXCEL_COLUMNS33"><xsl:with-param name="bars" select="$pQuestionCol"/></xsl:call-template>       
						<xsl:value-of select="$myLastStudentRow"/>, "(NR)")</f>					
						<v><xsl:value-of select="@correctResponses"/> </v>						
					</xsl:when>
					
					<xsl:when test="$ResponseType = 'ClassAveragePoints'"><xsl:attribute name="t">n</xsl:attribute>
					<v><xsl:value-of select="@ClassAveragePoints"/></v></xsl:when>				
					</xsl:choose>	
				</c>
		</xsl:for-each>
    </row>
  </xsl:template>	
  
  <xsl:template name="removeme_QUESTON_CORRECT_RESPONSES">
    <!-- My globals BEGIN FM when you get a chance see if you can make this global. -->	
        <xsl:variable name="numOfQuestions" select="count(/ROOT/SESSION/QUESTIONS/*)"/> 
 		<xsl:variable name="numOfStudents" select="count(/ROOT/SESSION/STUDENTS/*)"/> 
        <xsl:variable name="myFirstStudentRow" select="8"/> 
        <xsl:variable name="myLastStudentRow" select="8+($numOfStudents)-1"/>
		<xsl:variable name="myFirstQuestionCol" select="10"/> 			
        <xsl:variable name="myLastQuestionCol" select="6+($numOfQuestions)"/> 
		<xsl:variable name="myspans" select="concat('1:', $myLastQuestionCol)"/> 
		
		<xsl:variable name="row" select="4+8+$numOfStudents"/> 
<!-- END -->

	<row r="{$row}" s="27" customFormat="1" ht="16">
		<xsl:attribute name="spans"><xsl:value-of select="$myspans" /></xsl:attribute>
		<c r="A{$row}" s="11"/>
		<c r="B{$row}" s="11"/>
		<c r="C{$row}" s="11"/>
		<c r="D{$row}" s="63"/>		
		<c r="E{$row}" s="63"/>
		<c r="F{$row}" s="63"/>
		<c r="H{$row}" s="63"/>		
		<c r="I{$row}" s="14" t="inlineStr"> <is> <t>Correct Responses</t></is></c>
		
		<xsl:for-each select="ROOT/SESSION/QUESTIONS/question">
			<xsl:variable name="pQuestionCol" select="($myFirstQuestionCol)-1+position()" />
				<c s="39" t="n">
                <xsl:attribute name="r"><xsl:call-template name="EXCEL_COLUMNS33"><xsl:with-param name="bars" select="$pQuestionCol"/></xsl:call-template><xsl:value-of select="$row"/></xsl:attribute>
					<xsl:choose>
						<xsl:when test="position()  = 1">
							<xsl:attribute name="s">7</xsl:attribute>
						</xsl:when>
						<xsl:when test="position()  = last()">
							<xsl:attribute name="s">8</xsl:attribute>
						</xsl:when>
						<xsl:otherwise>
							<xsl:attribute name="s">6</xsl:attribute>
						</xsl:otherwise>
					</xsl:choose>
					
                   	<f>COUNTIF(<xsl:call-template name="EXCEL_COLUMNS33"><xsl:with-param name="bars" select="$pQuestionCol"/></xsl:call-template>		
					<xsl:value-of select="$myFirstStudentRow"/>:<xsl:call-template name="EXCEL_COLUMNS33"><xsl:with-param name="bars" select="$pQuestionCol"/></xsl:call-template>       
					<xsl:value-of select="$myLastStudentRow"/>, "&gt;0")</f>					
 					<v><xsl:value-of select="@correctResponses"/> </v>
				</c>
		</xsl:for-each>
  </row>
  </xsl:template>
  
  
   <xsl:template name="removeme_QUESTON_INCORRECT_RESPONSES">
    <!-- My globals BEGIN FM when you get a chance see if you can make this global. -->	
        <xsl:variable name="numOfQuestions" select="count(/ROOT/SESSION/QUESTIONS/*)"/> 
 		<xsl:variable name="numOfStudents" select="count(/ROOT/SESSION/STUDENTS/*)"/> 
        <xsl:variable name="myFirstStudentRow" select="8"/> 
        <xsl:variable name="myLastStudentRow" select="8+($numOfStudents)-1"/> 
        <xsl:variable name="myLastQuestionCol" select="6+($numOfQuestions)"/> 
		<xsl:variable name="myspans" select="concat('1:', $myLastQuestionCol)"/> 
		
		<xsl:variable name="row" select="5+8+$numOfStudents"/> 
<!-- END -->

	<row r="{$row}" s="27" customFormat="1" ht="16">
		<xsl:attribute name="spans"><xsl:value-of select="$myspans" /></xsl:attribute>
		<c r="A{$row}" s="11"/>
		<c r="B{$row}" s="11"/>
		<c r="C{$row}" s="11"/>
		<c r="E{$row}" s="63"/>
		<c r="F{$row}" s="14" t="inlineStr"> <is> <t>Incorrect Responses</t></is></c>
		<xsl:for-each select="ROOT/SESSION/QUESTIONS/question">
				<c s="39" t="n">
                <xsl:attribute name="r"><xsl:call-template name="EXCEL_COLUMNS33"><xsl:with-param name="bars" select="6+position()"/></xsl:call-template><xsl:value-of select="$row"/></xsl:attribute>
					<xsl:choose>
						<xsl:when test="position()  = 1">
							<xsl:attribute name="s">7</xsl:attribute>
						</xsl:when>
						<xsl:when test="position()  = last()">
							<xsl:attribute name="s">8</xsl:attribute>
						</xsl:when>
						<xsl:otherwise>
							<xsl:attribute name="s">6</xsl:attribute>
						</xsl:otherwise>
					</xsl:choose>
					
                   	<f>COUNTIF(<xsl:call-template name="EXCEL_COLUMNS33"><xsl:with-param name="bars" select="6+position()"/></xsl:call-template>		
					<xsl:value-of select="$myFirstStudentRow"/>:<xsl:call-template name="EXCEL_COLUMNS33"><xsl:with-param name="bars" select="6+position()"/></xsl:call-template>       
					<xsl:value-of select="$myLastStudentRow"/>, "0")</f>
                   
					<v><xsl:value-of select="@incorrectResponses"/> </v>
				</c>
		</xsl:for-each>
  </row>
  </xsl:template>
 
 
    <xsl:template name="removeme_QUESTON_N0_RESPONSES">
    <!-- My globals BEGIN FM when you get a chance see if you can make this global. -->	
        <xsl:variable name="numOfQuestions" select="count(/ROOT/SESSION/QUESTIONS/*)"/> 
 		<xsl:variable name="numOfStudents" select="count(/ROOT/SESSION/STUDENTS/*)"/> 
        <xsl:variable name="myFirstStudentRow" select="8"/> 
        <xsl:variable name="myLastStudentRow" select="8+($numOfStudents)-1"/> 
        <xsl:variable name="myLastQuestionCol" select="6+($numOfQuestions)"/> 
		<xsl:variable name="myspans" select="concat('1:', $myLastQuestionCol)"/> 
		
		<xsl:variable name="row" select="6+8+$numOfStudents"/> 
<!-- END -->

	<row r="{$row}" s="5" customFormat="1" ht="16">
		<xsl:attribute name="spans"><xsl:value-of select="$myspans" /></xsl:attribute>
		<c r="A{$row}" s="11"/>
		<c r="B{$row}" s="11"/>
		<c r="C{$row}" s="11"/>
		<c r="E{$row}" s="63"/>
		<c r="F{$row}" s="14" t="inlineStr"> <is> <t>No Responses</t></is></c>
		<xsl:for-each select="ROOT/SESSION/QUESTIONS/question">
				<c s="39" t="n">
                <xsl:attribute name="r"><xsl:call-template name="EXCEL_COLUMNS33"><xsl:with-param name="bars" select="6+position()"/></xsl:call-template><xsl:value-of select="$row"/></xsl:attribute>
					<xsl:choose>
						<xsl:when test="position()  = 1">
							<xsl:attribute name="s">34</xsl:attribute>
						</xsl:when>
						<xsl:when test="position()  = last()">
							<xsl:attribute name="s">36</xsl:attribute>
						</xsl:when>
						<xsl:otherwise>
							<xsl:attribute name="s">35</xsl:attribute>
						</xsl:otherwise>
					</xsl:choose>
					
                   	<f>COUNTIF(<xsl:call-template name="EXCEL_COLUMNS33"><xsl:with-param name="bars" select="6+position()"/></xsl:call-template>		
					<xsl:value-of select="$myFirstStudentRow"/>:<xsl:call-template name="EXCEL_COLUMNS33"><xsl:with-param name="bars" select="6+position()"/></xsl:call-template>       
					<xsl:value-of select="$myLastStudentRow"/>,"(NR)")</f>
                   
					<v><xsl:value-of select="@noResponses"/> </v>
				</c>
		</xsl:for-each>
  </row>
  </xsl:template>

</xsl:stylesheet>
