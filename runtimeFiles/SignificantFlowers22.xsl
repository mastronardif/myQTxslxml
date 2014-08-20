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
 <xsl:variable name="Qidx" select="6"/>
 <xsl:variable name="sigChars" select="1"/>

 <xsl:template match="ssn/p[@idx='6']">
 <xsl:call-template name="makeSignificant01" />
  </xsl:template>
  

 <xsl:template match="ssn/p[@idx=$Qidx+999]">
 <xsl:call-template name="makeRespLs" />
  </xsl:template>
 <!-- <xsl:template match="ssn/makeSignificant01/Original/p[@idx='6']">
 <xsl:template match="ssn/makeRespLs/p[@idx='5']">
    <xsl:call-template name="makeRespLs" />
 </xsl:template>  -->


<xsl:template name="makeVs">
<!-- set I begin -->
<fffffffff/>

<xsl:variable name="makeVs00">
<xsl:for-each select="v">
<xsl:copy-of select="." />
</xsl:for-each>
</xsl:variable>
<xsl:copy-of select="$makeVs00" />
</xsl:template>

<xsl:template name="makeRespLs">
    <xsl:param name="pVotes"/>

<!-- <Original><xsl:copy-of select="." /></Original> -->
<!-- <xsl:variable name="makeVs00">
<xsl:call-template name="makeVs" />
</xsl:variable> -->
<!-- <xsl:copy-of select="$makeVs00" /> -->

<tots>
    <countOf_v><xsl:value-of select="count(v)"/></countOf_v>
</tots>

<makeRespLs fm="The aggregate w/ out keys">
<!-- <xsl:copy-of select="." /> -->


<xsl:variable name="makeRespLs00">

<!-- set I begin -->
 <!-- <xsl:for-each select="v"> -->
 <xsl:for-each select="$pVotes/v">
    <!-- <xsl:sort select ="substring(@fans,1, $sigChars)"/> -->
    <xsl:sort select ="upper-case(substring(@fans,1, $sigChars))"/>
    <xsl:choose>
    <xsl:when test="name(.) = 'v'">
    <row>

    <xsl:attribute name="sig_{name(.)}">
         <!-- <xsl:value-of select ="substring(@fans,1, $sigChars)"/>-->
         <xsl:value-of select ="upper-case(substring(@fans,1, $sigChars))"/>
    </xsl:attribute>
    </row>
<!--
        <xsl:copy-of select="." />
        -->
    </xsl:when>
    </xsl:choose>
 </xsl:for-each>
</xsl:variable>

<!-- <xsl:copy-of select="$makeRespLs00"/> -->


<!-- ******************************* -->
<!-- ******************************* -->
<!-- set II begin -->

<xsl:variable name="makeRespLs00">
<!-- <row rid="-1" rs2="1" sig_v="````````"/> -->
 <xsl:for-each select="$makeRespLs00/row">

<xsl:if test="position() = 1">
<row n="set II">
<xsl:attribute name="rs2"><xsl:value-of select="position()"/></xsl:attribute>
<xsl:attribute name="rs20"><xsl:value-of select="'null'"/></xsl:attribute>
<xsl:attribute name="sig_v"><xsl:value-of select="@sig_v"/></xsl:attribute>
<xsl:attribute name="pos"><xsl:value-of select="'first'"/></xsl:attribute>
</row>
</xsl:if>

<!-- sequence change -->
<xsl:if test= "position() != 1 and @sig_v !=  preceding::row[1]/@sig_v">

<row n="set II an rc">
<xsl:attribute name="rs2"><xsl:value-of select="position()"/></xsl:attribute>
<xsl:attribute name="rs20"><xsl:value-of select="'null'"/></xsl:attribute>
<xsl:attribute name="sig_v"><xsl:value-of select="@sig_v"/></xsl:attribute>
<xsl:attribute name="pos"><xsl:value-of select="'middle'"/></xsl:attribute>
</row>

</xsl:if>
<xsl:if test="position() = last()">
    <row n="set II">
        <xsl:attribute name="rs2"><xsl:value-of select="position()"/></xsl:attribute>
        <xsl:attribute name="rs20"><xsl:value-of select="'null'"/></xsl:attribute>
        <xsl:attribute name="sig_v"><xsl:value-of select="@sig_v"/></xsl:attribute>
        <xsl:attribute name="pos"><xsl:value-of select="'last'"/></xsl:attribute>
    </row>

</xsl:if>
</xsl:for-each>
</xsl:variable>

<!-- ******************************* -->
<!-- ******************************* -->
<!-- <xsl:copy-of select="$makeRespLs00"/> -->
<!-- end  -->


<fmdebug msg="set III"/>
<xsl:variable name="makeRespLs00">
 <xsl:for-each select="$makeRespLs00/row">
  <xsl:choose>

  <!-- sequence change -->

  <xsl:when test= "position() =  last()">
<row>
<xsl:attribute name="b4_sig_v">
<xsl:value-of select="preceding::row[1]/@sig_v" />
</xsl:attribute>
<xsl:attribute name="b4_count">
<xsl:value-of select="1+(@rs2)-preceding::row[1]/@rs2" />
</xsl:attribute>

<!--
<xsl:attribute name="b4_rs1"><xsl:value-of select="preceding::row[1]/@rs2" /></xsl:attribute>
<xsl:attribute name="b4_rs2"><xsl:value-of select="(@rs2)" /></xsl:attribute>
-->
<xsl:attribute name="last"><xsl:value-of select="'last row'"/></xsl:attribute>
</row>

<xsl:if test="@sig_v !=  preceding::row[1]/@sig_v">
<row v="difPrec">
<xsl:attribute name="b4_sig_v">
<xsl:value-of select="preceding::row[1]/@sig_v" />
</xsl:attribute>
<xsl:attribute name="b4_count">
<xsl:value-of select="(@rs2)-preceding::row[1]/@rs2" />
</xsl:attribute>

<!--
<xsl:attribute name="b4_rs1"><xsl:value-of select="preceding::row[1]/@rs2"/></xsl:attribute>
<xsl:attribute name="b4_rs2"><xsl:value-of select="(@rs2)-1"/></xsl:attribute>


<xsl:attribute name="rs2"><xsl:value-of select="@rs2" /></xsl:attribute>
<xsl:attribute name="rs20"><xsl:value-of select="preceding::row[1]/@rs2" /></xsl:attribute>

<xsl:attribute name="rsCount"><xsl:value-of select="(@rs2)-(preceding::row[1]/@rs2)" /></xsl:attribute>

<xsl:attribute name="sig_v"><xsl:value-of select="@sig_v" /></xsl:attribute>
-->
</row>

</xsl:if>
</xsl:when>

  <xsl:when test= "@sig_v !=  preceding::row[1]/@sig_v">
<row>
<xsl:attribute name="b4_sig_v">
<xsl:value-of select="preceding::row[1]/@sig_v" />
</xsl:attribute>
<xsl:attribute name="b4_count">
<xsl:value-of select="(@rs2)-preceding::row[1]/@rs2" />
</xsl:attribute>
</row>

</xsl:when>

<!-- -->
  </xsl:choose>
</xsl:for-each>
</xsl:variable>
<!-- end  -->


 <!-- <xsl:copy-of select="$makeRespLs00"/>-->
<respLs>
<xsl:attribute name="b4_sigChars"><xsl:value-of select="$sigChars" /></xsl:attribute>
<xsl:attribute name="b4_Qidx"><xsl:value-of select="$Qidx" /></xsl:attribute>

<xsl:copy-of select="$makeRespLs00"/>

<tots>
<FMDEBUG msg="sum of the individual votes foreach group "/>
    <countOf_v><xsl:value-of select="sum($makeRespLs00/row/@b4_count)"/></countOf_v>
</tots>
</respLs>

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
                <xsl:attribute name="{name(.)}"><xsl:value-of select="."/></xsl:attribute>
            </xsl:otherwise>
    </xsl:choose>
    </xsl:for-each>


    <!-- for each element -->
    <xsl:for-each select="./*">

        <xsl:choose>
              <!-- <xsl:when test="@respLS">-->
              <xsl:when test="name(.) = 'respLs'">
<!-- Skip we will add at the end -->
<!--
 <xsl:template match="ssn/p[@idx=$Qidx+999]">
 <xsl:call-template name="makeRespLs" />
  </xsl:template>
   <fmdebug msg="replace replace replace replace"/>
  -->
        </xsl:when>

<!-- ******************************************************************* -->
        <xsl:when test="name(.) = 'v'">
            <original1/> <xsl:copy-of select="." /> <_original2/>
            <xsl:element name="{name(.)}DUCK">

            <xsl:for-each select="./@*">

<xsl:choose>

              <xsl:when test="name(.) = 'ansO'">
                <!-- Skip we will add at the end -->
              </xsl:when>

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


<xsl:choose>
    <xsl:when test="not(./@ansO)">
        <xsl:attribute name="ansO"><xsl:value-of select="@ans"/></xsl:attribute>
    </xsl:when>
    <xsl:otherwise> <!-- unchanged! -->
        <xsl:attribute name="ansO"><xsl:value-of select="@ansO"/></xsl:attribute>
    </xsl:otherwise>
</xsl:choose>
            </xsl:element>


        </xsl:when>
        <!-- ******************************************************************* -->

                 <!-- Ignore other emlements -->
                 <xsl:otherwise>
                    <xsl:copy-of select="." />
                 </xsl:otherwise>
         </xsl:choose>
    </xsl:for-each>



<xsl:variable name="theVs">
    <xsl:call-template name="makeVs"/>
</xsl:variable>

<fmdebug msg="the votes 11"/>
 <xsl:copy-of select="$theVs" />
<fmdebug msg="the votes 22"/>

    <!-- if ____ not exists add it -->
<xsl:if test="not(./respLsFUCK)">
<fmdebug msg="WAS NOT THEIR NEW NEW NEW NEW"/>

    <xsl:call-template name="makeRespLs">
        <xsl:with-param name="pVotes" select="$theVs"/>
    </xsl:call-template>
<!--
 <xsl:template match="ssn/p[@idx=$Qidx+999]">
 <xsl:call-template name="makeRespLs" />
  </xsl:template>
  -->
  <fmdebug msg="replace replace replace replace"/>

</xsl:if>

</xsl:element>
</newsh_t>
</makeSignificant01>

</xsl:template>

</xsl:stylesheet>
