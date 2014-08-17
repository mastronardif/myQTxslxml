<?xml version="1.0" encoding="utf-8"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
<!-- Significant characters question updating w/ out xslt keys! Sorry -->
<!-- Import the identity transformation. -->

 <!--
 http://www.dpawson.co.uk/xsl/sect2/N8090.html - this guy knows his s
   <xsl:import href="Identity.xsl"/>
  -->
   <xsl:template match="node()|@*">
    <xsl:copy>
      <xsl:apply-templates select="@*|node()"/>
    </xsl:copy>
  </xsl:template>

 <!-- <xsl:variable name="sigChars" select="3"/> <xsl:variable name="sigChars" select="%1"/>-->
<!-- <xsl:variable name="sigChars" select="3"/>
 <xsl:template match="ssn/p[@idx='666']">
 <xsl:call-template name="makeSignificant01" />
  </xsl:template> -->

<xsl:variable name="sigChars" select="1"/>
 <xsl:template match="ssn/p[@idx='6']">
 <xsl:call-template name="makeRespLs" />
  </xsl:template>
 <!-- <xsl:template match="ssn/makeSignificant01/Original/p[@idx='6']">
 <xsl:template match="ssn/makeRespLs/p[@idx='5']">
    <xsl:call-template name="makeRespLs" />
 </xsl:template>  -->

<xsl:template name="makeRespLs">
<Original><xsl:copy-of select="." /></Original>
<tots>
    <countOf_v><xsl:value-of select="count(v)"/></countOf_v>
</tots>
<makeRespLs fm="holy f in s I might be able to do w/ out keys">
<!-- <xsl:copy-of select="." /> -->


<xsl:variable name="makeRespLs00">
<row rid="-1" sig_v="substring(12345678901234567890,1, $sigChars)"/>
<v fans="Bogus louie hobston" tscr="0" ans="" att="" tm="" fanst="" scr="" lto="" id=""/>

 <xsl:for-each select="v">
    <xsl:sort select ="substring(@fans,1, $sigChars)"/>
    <xsl:choose>
    <xsl:when test="name(.) = 'v'">
    <row>
    <xsl:attribute name="rid">
<xsl:value-of select="position()"/>
    </xsl:attribute>

    <xsl:attribute name="sig_{name(.)}">
         <xsl:value-of select ="substring(@fans,1, $sigChars)"/>
    </xsl:attribute>
    </row>
        <xsl:copy-of select="." />
    </xsl:when>
    </xsl:choose>
 </xsl:for-each>
</xsl:variable>

<fmdebug msg="set I"/>
<xsl:copy-of select="$makeRespLs00"/>

<!-- set II begin -->
<fmdebug msg="set II"/>
<xsl:variable name="makeRespLs00">
<row rid="-1" rs2="1" sig_v="````````"/>
 <xsl:for-each select="$makeRespLs00/row">
  <xsl:choose>
  <!-- sequence change -->
  <xsl:when test= "@sig_v !=  preceding::row[1]/@sig_v">
<row>

<xsl:attribute name="rs2">
<xsl:value-of select="position()" />
</xsl:attribute>

<xsl:attribute name="rs20">
<xsl:value-of select="'null'" />
</xsl:attribute>

<xsl:attribute name="sig_v">
<xsl:value-of select="@sig_v" />
</xsl:attribute>
</row>
</xsl:when>
  </xsl:choose>
</xsl:for-each>
</xsl:variable>

<fmdebug msg="set II"/>
<xsl:copy-of select="$makeRespLs00"/>
<!-- end  -->


<fmdebug msg="set III"/>
<xsl:variable name="makeRespLs00">
 <xsl:for-each select="$makeRespLs00/row">
  <xsl:choose>

  <!-- sequence change -->


  <xsl:when test= "@sig_v !=  preceding::row[1]/@sig_v">
<row>
<xsl:attribute name="b4_sig_v">
<xsl:value-of select="preceding::row[1]/@sig_v" />
</xsl:attribute>
<xsl:attribute name="b4_count">
<xsl:value-of select="(@rs2)-preceding::row[1]/@rs2" />
</xsl:attribute>

<xsl:attribute name="b4_rs1">
<xsl:value-of select="preceding::row[1]/@rs2" />
</xsl:attribute>
<xsl:attribute name="b4_rs2">
<xsl:value-of select="(@rs2)-1" />
</xsl:attribute>

<xsl:attribute name="rs2">
<xsl:value-of select="@rs2" />
</xsl:attribute>
<xsl:attribute name="rs20">
<xsl:value-of select="preceding::row[1]/@rs2" />
</xsl:attribute>

<xsl:attribute name="rsCount">
<xsl:value-of select="(@rs2)-(preceding::row[1]/@rs2)" />
</xsl:attribute>

<xsl:attribute name="sig_v">
<xsl:value-of select="@sig_v" />
</xsl:attribute>
</row>

  <xsl:if test= "position() =  last()">
<row>
<xsl:attribute name="b4_sig_v">
<xsl:value-of select="@sig_v" />
</xsl:attribute>
<xsl:attribute name="b4_count">
<xsl:value-of select="(@rs2)-preceding::row[1]/@rs2" />
</xsl:attribute>

<xsl:attribute name="b4_rs1">
<xsl:value-of select="preceding::row[1]/@rs2" />
</xsl:attribute>
<xsl:attribute name="b4_rs2">
<xsl:value-of select="(@rs2)" />
</xsl:attribute>
</row>
</xsl:if>

</xsl:when>

<!--
  <xsl:when test= "position() =  last()">
<row>
<xsl:attribute name="b4_sig_v">
<xsl:value-of select="@sig_v" />
</xsl:attribute>
<xsl:attribute name="b4_count">
<xsl:value-of select="(@rs2)-preceding::row[1]/@rs2" />
</xsl:attribute>

<xsl:attribute name="b4_rs1">
<xsl:value-of select="preceding::row[1]/@rs2" />
</xsl:attribute>
<xsl:attribute name="b4_rs2">
<xsl:value-of select="(@rs2)" />
</xsl:attribute>
</row>
</xsl:when>
-->
  </xsl:choose>
</xsl:for-each>
</xsl:variable>
<!-- end  -->


 <!-- <xsl:copy-of select="$makeRespLs00"/> -->
<respLs>
<xsl:copy-of select="$makeRespLs00"/>

<tots>
    <countOf_v><xsl:value-of select="sum($makeRespLs00/row/@b4_count)"/></countOf_v>
</tots>
</respLs>
<fmdebug/>


<fmdebug msg="the aggregate - group-by significant fans /w count "/>

 <xsl:for-each select="$makeRespLs00/crow">
  <xsl:choose>

<!--
    <xsl:when test="position()  = last()">
        <xsl:call-template name="myCount">
            <xsl:with-param name="myNode" select="$makeRespLs00"/>
            <xsl:with-param name="myKey" select="substring(@fans,1, 3)"/>
        </xsl:call-template> <xsl:value-of select ="substring(@fans,1, 3)"/> <xsl:copy-of select="." />
    <xsl:value-of select ="position()"/>last
    </xsl:when>
-->

<xsl:when test="position()  = 1">
<xsl:variable name="cnt">
<xsl:call-template name="myCount">
        <xsl:with-param name="myNode" select="$makeRespLs00"/>
        <xsl:with-param name="myKey" select="substring(@fans,1, $sigChars)"/>
    </xsl:call-template>
</xsl:variable>


<respR>
<xsl:attribute name="r1">
<xsl:value-of select="position()" />
</xsl:attribute>
<xsl:attribute name="respCP">
<xsl:value-of select="concat($cnt, ',', 'wtf_points')" />
</xsl:attribute>
<xsl:attribute name="sigAns">
<xsl:value-of select="substring(@fans,1,$sigChars)"/>
</xsl:attribute>
</respR>
</xsl:when>

    <!-- sequence change -->
    <xsl:when test= "substring(@fans,1, $sigChars) !=  substring(preceding::row[1]/@sig_v,1,$sigChars)">



<xsl:variable name="cnt">
<xsl:call-template name="myCount">
        <xsl:with-param name="myNode" select="$makeRespLs00"/>
        <xsl:with-param name="myKey" select="substring(@sig_v,1, $sigChars)"/>
    </xsl:call-template>
</xsl:variable>


<respR>

    <xsl:attribute name="C_fuckR1">
    <xsl:value-of select="position()"/>
    <!-- <xsl:value-of select="substring(preceding::row[1]/@rid,1,$sigChars)"/> -->
    </xsl:attribute>
<xsl:attribute name="r1">
<xsl:value-of select="position()" />
</xsl:attribute>

<xsl:attribute name="respCP">
<xsl:value-of select="concat($cnt, ',', position(),  'wtf_points')" />
</xsl:attribute>
<xsl:attribute name="sigAns">
<xsl:value-of select="substring(@sig_v,1,$sigChars)"/>
</xsl:attribute>
</respR>


<!--
<xsl:call-template name="myCount">
    <xsl:with-param name="myNode" select="$makeRespLs00"/>
    <xsl:with-param name="myKey" select="substring(@fans,1, $sigChars)"/>
</xsl:call-template> [<xsl:value-of select ="substring(@fans,1, $sigChars)"/>] <xsl:copy-of select="." />
<xsl:value-of select ="position()"/>
-->
</xsl:when>

  </xsl:choose>
</xsl:for-each>

</makeRespLs>
</xsl:template>

<xsl:template name="myCount">
<xsl:param name="myNode"/>
<xsl:param name="myKey"/>
<xsl:value-of select="count($myNode/row[@sig_v = $myKey])"/>
  <!--      <xsl:value-of select="count($myNode/v[substring(@fans,1, 3) = $myKey])"/> -->

<!--<xsl:value-of select="count($myNode/row[substring(@v,1, $sigChars) = $myKey])"/> -->
</xsl:template>
<!-- ////////////////////////////////// -->

<xsl:template name="makeSignificant01">

 <makeSignificant01>
    <Original><xsl:copy-of select="." /></Original>

<newsh_t>
<xsl:element name="{name(.)}">
    <xsl:for-each select="./@*">
    <xsl:choose>
        <xsl:when test="name(.) = 'sig'">
            <xsl:attribute name="{name(.)}"><xsl:value-of select="$sigChars"/></xsl:attribute>
        </xsl:when>

                            <xsl:otherwise>
                            <xsl:attribute name="{name(.)}">
                                <xsl:value-of select="."/>
                            </xsl:attribute>
                            </xsl:otherwise>
    </xsl:choose>
    </xsl:for-each>


    <!-- for each element -->
    <xsl:for-each select="./*">

        <xsl:choose>
              <!-- <xsl:when test="@respLS">-->
              <xsl:when test="name(.) = 'respLs'">
                <xsl:element name="{name(.)}"> <!-- respLs -->
                       <xsl:for-each select="./@*">

                            <xsl:attribute name="{name(.)}">
                                <xsl:value-of select="."/>
                            </xsl:attribute>
                        </xsl:for-each>

                        <!-- elements -->
                        <xsl:for-each select="./*">

                        <xsl:choose>

                            <xsl:when test="name(.) = 'respR'">
                               <!-- <xsl:copy-of select="." /> -->
                                <xsl:element name="{name(.)}">
                                    <!-- add new attrib or update -->

                                    <xsl:for-each select="./@*">
                                        <!-- <xsl:attribute name="{name(.)}">
                                        <xsl:value-of select="."/> </xsl:attribute> -->


<xsl:choose>
<xsl:when test="name(.) = 'respLS'">
<xsl:attribute name="{name(.)}"><xsl:value-of select="."/> </xsl:attribute>
<xsl:attribute name="sig_respLS"><xsl:value-of select="substring(.,1, $sigChars)"/> </xsl:attribute>
</xsl:when>
                            <xsl:otherwise> <!-- leave attributes unchanged -->
<xsl:copy-of select="." />
<!--  or this.                           <xsl:attribute name="{name(.)}"><xsl:value-of select="."/> </xsl:attribute>
-->
                            </xsl:otherwise>
                        </xsl:choose>

                                    </xsl:for-each>

                               </xsl:element>

                            </xsl:when>


                            <!-- other elements ignore -->
                            <xsl:otherwise>
                               <xsl:copy-of select="." />
                            </xsl:otherwise>
                        </xsl:choose>

                        </xsl:for-each>

                    </xsl:element> <!-- /respLs -->
              </xsl:when>



              <xsl:when test="name(.) = 'v'">
   <original1/> <xsl:copy-of select="." /> <_original2/>

                    <xsl:element name="{name(.)}DUCK">
                    <xsl:for-each select="./@*">

<xsl:choose>
<xsl:when test="name(.) = 'sig_ans'">
    <!-- have only one attrib by said name -->
</xsl:when>
<xsl:when test="name(.) = 'ans'">
   <xsl:attribute name="sig_{name(.)}"><xsl:value-of select="substring(.,1, $sigChars)"/> </xsl:attribute>
</xsl:when>

<xsl:otherwise>
   <xsl:copy-of select="." />
</xsl:otherwise>
</xsl:choose>

                    </xsl:for-each>
                    </xsl:element>
              </xsl:when>

                 <!-- Ignore other emlements -->
                 <xsl:otherwise>
                    <xsl:copy-of select="." />
                 </xsl:otherwise>
         </xsl:choose>
    </xsl:for-each>
</xsl:element>
</newsh_t>
</makeSignificant01>

</xsl:template>

</xsl:stylesheet>
