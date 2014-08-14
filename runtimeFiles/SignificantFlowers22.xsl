<?xml version="1.0" encoding="utf-8"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
<!-- Significant characters question updating w/ out xslt keys! sorry -->
<!-- Import the identity transformation. -->

 <!--
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

<xsl:variable name="sigChars" select="3"/>
 <xsl:template match="ssn/p[@idx='6']">
 <xsl:call-template name="makeRespLs" />
  </xsl:template>
 <!-- <xsl:template match="ssn/makeSignificant01/Original/p[@idx='6']">
 <xsl:template match="ssn/makeRespLs/p[@idx='5']">
    <xsl:call-template name="makeRespLs" />
 </xsl:template>  -->

<xsl:template name="makeRespLs">
<makeRespLs>
<!-- <xsl:copy-of select="." /> -->

  <xsl:variable name="xx">
    <html>
      <body>
      <ffffff/>
      </body>
    </html>
  </xsl:variable>
  <xsl:value-of select="$xx"/>

<!--  <xsl:for-each select="./*"> -->
<!-- <xsl:variable name="title">
 <xsl:choose> -->

 <xsl:for-each select="v[not(@fans=preceding-sibling::v/@fans)]">
<xsl:sort select ="substring(@fans,1, 3)"/>
<!--
    <xsl:sort select ="substring(@fans,1, 3)"/>
    <xsl:sort select ="@fans"/>
    -->

    <xsl:choose>
    <xsl:when test="name(.) = 'v'">
    <row>
    row(<xsl:value-of select="position()"/>) <xsl:value-of select ="substring(@fans,1, 3)"/> -
    </row>
        <xsl:copy-of select="." />

<!--
<xsl:value-of select="preceding::v[1]/@fans"/>
-->
    </xsl:when>
    </xsl:choose>


 </xsl:for-each>

<!-- </xsl:choose>
</xsl:variable> 

 <xsl:value-of select="$title" />
 -->
</makeRespLs>



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
